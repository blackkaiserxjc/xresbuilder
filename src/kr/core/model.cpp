#include <fstream>
#include <fmt/format.h>

#include "data_table.h"
#include "idl.h"

namespace kr {
namespace core {

namespace detail {

struct HeaderField {
  explicit HeaderField(int index = 0, const std::string &value = {},
                       const std::string &type = {}, int begin_index = 0,
                       int end_index = 0)
      : index{index}, value{value}, type{type},
        begin_index{begin_index}, end_index{end_index} {}

  int index;
  std::string value;
  std::string type;
  int begin_index;
  int end_index;
};

} // namespace detail


DataRow::DataRow(DataTable *parent, int row_number, const std::vector<std::string>& row)   
    :parent_(parent), row_number_(row_number)
{
    convert(row);
}

DataRow::~DataRow()
{
}

void DataRow::convert(const std::vector<std::string>& row)
{
    if (parent_ == nullptr || parent_->type().base_type != BASE_TYPE_OBJECT || !parent_->type().obj_def)
    {
        throw "invaild args";
    } 

    auto cvt = [&](auto&& obj)
    {   
        int begin = obj->begin_index;
        int end = obj->end_index;
        if (IsPod(obj->value.type.base_type))
        {
            return row[begin];
        }
        else if (IsArray(obj->value.type.base_type)) 
        {
            std::vector<std::string> results;
            for (auto index = begin; index != end; ++index)
            {
                if (!row[index].empty()) 
                {
                    results.push_back(row[index]);
                }
            }
            return fmt::format("[{}]", fmt::join(results, ";"));
        }
        return std::string("");
    };

    std::vector<std::string> fields;
    auto obj_def = parent_->type().obj_def;
    for (auto&& field_def :  obj_def->fields.vec) 
    {
        auto dest = cvt(field_def);
        if (!dest.empty())
        {
            fields.emplace_back(dest);
        }
    }
    auto source = fmt::format("{}", fmt::join(fields, ","));
    Packer<msgpack::packer<msgpack::sbuffer>> packer{buffer_};
    parse_data(source, packer);
}

DataTable::DataTable(const std::string &path)
    : doc_{}, n_rows_{}, n_cols_{}, root_type_{} 
{
    read_data(path);
}

DataTable::~DataTable()
{
}

void DataTable::load(const std::string& path)
{
    read_data(path);
}

void DataTable::clear()
{
    n_rows_ = n_cols_ = 0;
    data_.clear();
    doc_.Clear();
}

void DataTable::read_data(const std::string& path)
{
    std::ifstream stream;
    stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    stream.open(path, std::ios::binary);
    read_data(stream);
}

void DataTable::read_data(std::istream& stream)
{
    doc_.Load(stream, rapidcsv::LabelParams(-1, -1));
    n_rows_ = doc_.GetRowCount();
    n_cols_ = doc_.GetColumnCount();
    parse();
}

void DataTable::parse()
{       
    if (n_rows_ < static_cast<std::uint32_t>(HeaderRowIndex::START)) 
    {
        std::cout << "rows less start row index." << std::endl;
        return ;
    }

    if (!parse_header())
    {
        std::cout << "parse header failed." << std::endl;
        return ;
    }
    parse_data();
}

bool DataTable::parse_header()
{
    auto type_row = doc_.GetRow<std::string>(static_cast<std::uint32_t>(HeaderRowIndex::TYPE));
    auto value_row = doc_.GetRow<std::string>(static_cast<std::uint32_t>(HeaderRowIndex::VALUE));
    if (type_row.empty() || value_row.empty() || type_row.size() != value_row.size()) 
    {
        std::cout << "type row or value row is empty." << std::endl;
        return false;
    }

    std::vector<int> field_indexs;
    for (auto i = 0; i < n_cols_; i++)
    {
        if (!type_row[i].empty())
        {
            field_indexs.push_back(i);
        }
    }
    std::vector<detail::HeaderField> fields;
    int field_index_size = field_indexs.size();
    for (auto i = 0; i < field_index_size; i++)
    {
        auto cur_index = field_indexs[i];
        auto next_index = (i == field_index_size - 1) ? (n_cols_) : (field_indexs[i + 1]);
        fields.emplace_back(i, value_row[cur_index], type_row[cur_index], cur_index, next_index);
    }

    auto object_def = std::make_shared<ObjectDef>();
    root_type_.base_type = BASE_TYPE_OBJECT;
    root_type_.obj_def = object_def;
    std::for_each(fields.begin(), fields.end(), [&](auto&& field)
    {   
        Type child_type;
        if (!parse_field(field.type, child_type))
        {
            std::cout << field.value << "parse error." << std::endl;
            return ;
        }
        auto field_def = std::make_shared<FieldDef>();
        field_def->value.type = child_type;
        field_def->index = field.index;
        field_def->name = field.value;
        field_def->begin_index = field.begin_index;
        field_def->end_index = field.end_index;
        object_def->fields.Add(field.value, field_def);
    });
    return true;
}

bool DataTable::parse_data()
{
    auto start_index = static_cast<std::uint32_t>(HeaderRowIndex::START);
    for (auto index = start_index; index < n_rows_; index++)
    {
        auto row = doc_.GetRow<std::string>(index);
        if (!row.empty())
        {
            data_.emplace(index, std::make_shared<DataRow>(this, index, row));
        }
    }
    return true;
}

}
}
#include <fstream>

#include "data_table.h"
#include "idl.h"

namespace kr {
namespace core {

namespace detail {
struct HeaderField {
  explicit HeaderField(int index = 0, const std::string &value = {}, const std::string &type = {},
              int begin_index = 0, int end_index = 0)
      : index{index}, value{value}, type{type},
        begin_index{begin_index}, end_index{end_index} {}

  int index;
  std::string value;
  std::string type;
  int begin_index;
  int end_index;
};
} // namespace detail

DataTable::DataTable(const std::string &path)
    : doc_{}, n_rows{}, n_cols{}, type{} 
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

void DataTable::read_data(std::ifstream& stream)
{
    doc_.Load(stream);
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
    parse_header();
    parse_data();
}

void DataTable::parse_header()
{
    auto type_row = doc_.GetRow(static_cast<std::uint32_t>(HeaderRowIndex::TYPE));
    auto value_row = doc_.GetRow(static_cast<std::uint32_t>(HeaderRowIndex::VALUE));
    if (type_row.empty() || value_row.empty() || type_row.size() != value_row.size()) 
    {
        std::cout << "type row or value row is empty." << std::endl;
        return ;
    }

    std::vector<int> field_indexs;
    for (auto i = 0; i < n_cols_; i++)
    {
        if (!type_row[i].empty())
        {
            fields.push_back(i);
        }
    }
    std::vector<detail::HeaderField> fields;
    int field_index_size = field_indexs.size();
    for (auto i = 0; i < field_index_size; i++)
    {
        auto cur_index = field_indexs[i];
        auto next_index = (i == field_index_size - 1) ? (n_cols_ - 1) : (field_index_size[i + 1] - 1);
        fields.emplace_back(i, value_row[cur_index], type_row[cur_index], cur_index, next_index);
    }

    auto object_def = std::make_shared<ObjectDef>();
    type_.base_type = BASE_TYPE_OBJECT;
    type_.object_def = object_def;
    std::for_each(fields.begin(), fields.end(), [&](auto&& field)
    {   
        Type child_type;
        if (!parse_field(field.type, child_type))
        {
            std::cout << field.value << "parse error." << std::endl;
            return;
        }
        auto field_def = std::make_shared<FieldDef>();
        field_def.index = field.index;
        field_def.name = field.value;
        field_def.begin_index = field.begin_index;
        field_def.end_index = field.end_index;
        field_def.type = child_type;
        object_def.fields.Add(field.value, field_def);
    });
}

void DataTable::parse_data()
{

}

}
}
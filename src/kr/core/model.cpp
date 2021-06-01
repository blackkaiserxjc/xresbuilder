#include <fmt/format.h>

#include <kr/core/model.h>


namespace kr {
namespace core {

Object::Object(Model& model, DataRow& data)
    :id_(data.id()), model_(model)
{
    init(data);
}

Object::~Object()
{
}

void Object::init(DataRow& data)
{
    std::vector<std::string> fields;
    auto& columns = data.columns();
    for(auto index = 0; index < columns.count(); index++)
    {
        auto& column = columns[index];
        if (!column.value().empty())
        {
            fields.emplace_back(column.value());
        }
    }
    value_ = fmt::format("{}", fmt::join(fields, ","));
    pack_buffer(value_);
}

void Object::pack_buffer(const std::string& source)
{
    Packer<msgpack::packer<msgpack::sbuffer>> packer{buffer_};
    parse_data(source, packer);
}

Model::Model(DataTable& table)
    :table_def_{}
{
    parse(table);
}

Model::~Model()
{
}

void Model::parse(DataTable& table)
{
    parse_table_def(table);
    parse_table_data(table);
}

void Model::parse_table_def(DataTable& table)
{
    auto obj_def = std::make_shared<ObjectDef>();
    table_def_.base_type = BASE_TYPE_OBJECT;
    table_def_.obj_def = obj_def;

    auto& columns = table.columns();
    for (auto index = 0; index < columns.count(); index++)
    {
        auto& column = columns[index];
        Type child_type;
        if (!parse_field(column.value(), child_type))
        {
            return ;
        }
        auto field_def = std::make_shared<FieldDef>();
        field_def->value.type = child_type;
        field_def->index = column.index();
        field_def->name = column.name();
        obj_def->fields.Add(column.name(), field_def);
    }
}

void Model::parse_table_data(DataTable& table)
{
    auto& collect = table.rows();
    for(auto index = 1; index <= collect.count(); index++)
    {
        data_.emplace(index, std::make_shared<Object>(*this, collect[index]));
    }
}

}
}
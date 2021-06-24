#include <boost/algorithm/string.hpp>
#include <fmt/format.h>

#include <kr/core/model.h>
#include <kr/core/parser.h>

namespace kr {
namespace core {

Object::Object(Model &model, DataRow &data)
    : id_(data.id()), model_(model)
{
    init(data);
}

Object::~Object()
{
}

void Object::init(DataRow &data)
{
    std::vector<std::string> fields;
    auto &columns = data.columns();
    for (size_t index = 0; index < columns.count(); index++)
    {
        auto &column = columns[index];
        if (!column.value().empty())
        {
            fields.emplace_back(column.value());
        }
    }
    value_ = fmt::format("{}", fmt::join(fields, ","));
    pack_buffer(value_);
}

void Object::pack_buffer(const std::string &source)
{
	try {
		auto parser = model_.parser();
		Packer<msgpack::packer<msgpack::sbuffer>> packer{buffer_};
		parser->parse_object(source, packer);
	}
	catch (std::exception& e) {
		throw fmt::format("compile error: row = {}, info = {}.", id_, e.what());
	}
}

Model::Model(DataTable &table)
    : table_def_{}, parser_(std::make_shared<Parser>())
{
    parse(table);
}

Model::~Model()
{
}

void Model::parse(DataTable &table)
{
    parse_table_def(table);
    parse_table_data(table);
}

void Model::parse_table_def(DataTable &table)
{
    auto obj_def = std::make_shared<ObjectDef>();
    table_def_.base_type = BASE_TYPE_OBJECT;
    table_def_.obj_def = obj_def;

    auto &columns = table.columns();
    for (size_t index = 0; index < columns.count(); index++)
    {
        auto &column = columns[index];
        try
        {
            Type child_type;
            if (!parser_->parse_field(column.value(), child_type))
            {
                return;
            }
            auto field_def = std::make_shared<FieldDef>();
            field_def->value.type = child_type;
            field_def->index = column.index();
            parse_table_ki(field_def, child_type.base_type, column.index(), column.name());
            obj_def->fields.add(field_def->name, field_def);
        }
        catch (std::exception& e)
        {
            throw fmt::format("compile error: column = {}, info = {}.", index + 1, e.what());
        }
    }
}

void Model::parse_table_ki(std::shared_ptr<FieldDef> field_def,
    uint32_t base_type, uint32_t field_index,
    const std::string &name)
{
    if (IsPod(static_cast<BaseType>(base_type)) && !field_index)
    {
        field_def->is_key = true;
        field_def->name = name;
        return;
    }

    std::vector<std::string> results;
    boost::split(results, name, boost::is_any_of(":"), boost::token_compress_on);
    if (results.size() != 2)
    {
        field_def->name = name;
        return;
    }

    auto &back = results.back();
    field_def->name = results.front();
    if (back == "k" || back == "K")
    {
        field_def->is_key = true;
    }
    else if (back == "i" || back == "I")
    {
        field_def->is_index = true;
    }
}

void Model::parse_table_data(DataTable &table)
{
    auto &collect = table.rows();
    for (size_t index = 1; index <= collect.count(); index++)
    {
        data_.emplace(index, std::make_shared<Object>(*this, collect[index]));
    }
}

} // namespace core
} // namespace kr
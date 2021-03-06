#include <locale>
#include <string>

#include <boost/algorithm/string.hpp>
#include <fmt/format.h>

#include <kr/core/code_generator.h>
#include <kr/core/generator_helpers.h>
#include <kr/core/idl.h>
#include <kr/utility/utility.h>

namespace kr {
namespace core {

struct LuaVisitor : public msgpack::null_visitor
{
    struct Context
    {
        Context()
            : row{}, field{}
        {
        }
        int row;
        std::string field;
    };

    LuaVisitor(std::string &writer, uint32_t field_name_case,
        uint32_t indent_step)
        : writer_{writer}, field_name_case_{field_name_case}, indent_step_{indent_step}, ctx_{}, map_level_{}
    {
    }

    bool visit_null()
    {
        writer_ += "nil";
        return true;
    }

    bool visit_boolean(bool v)
    {
        if (v)
        {
            writer_ += "true";
        }
        else
        {
            writer_ += "false";
        }
        return true;
    }

    bool visit_positive_integer(uint64_t v)
    {
        writer_ += std::to_string(v);
        return true;
    }

    bool visit_negative_integer(int64_t v)
    {
        writer_ += std::to_string(v);
        return true;
    }

    bool visit_float32(float v)
    {
        writer_ += std::to_string(v);
        return true;
    }

    bool visit_float64(double v)
    {
        writer_ += std::to_string(v);
        return true;
    }

    bool visit_str(const char *v, uint32_t size)
    {
        auto key = std::string(v, size);
        if (is_map_key)
        {
            key = to_case_name(key);
        }

        if (is_map_key && map_level_ == 1)
        {
            ctx_.field = key;
        }
        writer_ += fmt::format("\"{}\"", key);
        return true;
    }

    bool start_array(uint32_t num_elements)
    {
        current_size_.emplace_back(0, num_elements);
        indent();
        writer_ += "{";
        return true;
    }

    bool start_array_item()
    {
        auto &&[index, size] = current_size_.back();
        index++;
        write_indent();
        writer_ += fmt::format("[{}] = ", index);
        return true;
    }

    bool end_array_item()
    {
        writer_ += ",";
        return true;
    }

    bool end_array()
    {
        current_size_.pop_back();
        outdent();
        write_indent();
        writer_ += "}";
        return true;
    }

    bool start_map(uint32_t num_kv_pairs)
    {
        if (!map_level_)
        {
            ctx_.row++;
        }
        ++map_level_;
        current_size_.emplace_back(0, num_kv_pairs);
        indent();
        writer_ += "{";
        return true;
    }

    bool start_map_key()
    {
        write_indent();
        writer_ += "[";
        is_map_key = true;
        return true;
    }

    bool end_map_key()
    {
        writer_ += "] = ";
        is_map_key = false;
        return true;
    }

    bool start_map_value()
    {
        return true;
    }

    bool end_map_value()
    {
        writer_ += ",";
        return true;
    }

    bool end_map()
    {
        current_size_.pop_back();
        --map_level_;
        outdent();
        write_indent();
        writer_ += "}";
        return true;
    }

    void parse_error(size_t parsed_offset, size_t error_offset)
    {
        throw fmt::format(
            "msgpack parse_error : row = {}, field = {}.", ctx_.row, ctx_.field);
    }

    void insufficient_bytes(size_t parsed_offset, size_t error_offset)
    {
        throw fmt::format(
            "msgpack insufficient_error : row = {}, field = {}.", ctx_.row, ctx_.field);
    }

private:
    std::string to_case_name(const std::string &input)
    {
        if (field_name_case_ == IDLOptions::NamingStyle::kCamelCase)
        {
            return generator::underscores_to_camelcase(input);
        }
        else if (field_name_case_ == IDLOptions::NamingStyle::kPascalCase)
        {
            return generator::underscores_to_pascalcase(input);
        }
        else
        {
            return input;
        }
    }

    void indent()
    {
        indent_string_ += std::string(indent_step_, ' ');
    }

    void outdent()
    {
        assert(indent_string_.size() >= indent_step_);
        indent_string_.resize(indent_string_.size() - indent_step_);
    }

    void write_indent()
    {
        writer_ += fmt::format("\n{}", indent_string_);
    }

    std::string &writer_;
    uint32_t depath_;
    std::vector<std::tuple<uint32_t, uint32_t>> current_size_;
    uint32_t field_name_case_;
    bool is_map_key;
    uint32_t indent_step_;
    std::string indent_string_;
    uint32_t map_level_;
    Context ctx_;
};

class LuaGenerator : public CodeGenerator
{
public:
    LuaGenerator(Model &model, const IDLOptions &opts, const std::string &path,
        const std::string &file_name)
        : CodeGenerator(model, opts, path, file_name), code_(std::string(opts.indent_step, ' '))
    {
    }
    ~LuaGenerator()
    {
    }

    bool generate() override
    {
        code_.clear();
        msgpack::sbuffer buffer;
        Packer<msgpack::packer<msgpack::sbuffer>> packer{buffer};
        model_.serialize(packer);

        auto table_def = model_.type();

        code_ +=
            "--[[\n// <auto-generated>\n"
            "// "
            + std::string(generated_warning()) +
            "\n"
            "// </auto-generated>\n--]]\n";

        code_ += "local M = {}";
        generate_ki_func(table_def);
        code_ += "M[\"table\"] = ";

        std::size_t offset = 0;
        std::string table;
        LuaVisitor visitor(table, opts_.field_naming_style, opts_.indent_step);
        msgpack::parse(buffer.data(), buffer.size(), offset, visitor);

        code_ += table;
        code_ += "\n";
        generate_ki_map(table_def);
        code_ += "return M";

        const std::string file_path = generated_filename(path_, file_name_);
        const std::string final_code = code_.to_string();
        return kr::utility::save_file(file_path.c_str(), final_code, false);
    }

    std::string generated_filename(const std::string &path,
        const std::string &file_name) override
    {
        std::string extension = ".lua";
        if (!opts_.extension.empty())
        {
            extension = opts_.extension;
        }
        auto case_name = file_name;
        switch (opts_.filename_naming_style)
        {
        case IDLOptions::kCamelCase:
            case_name = generator::underscores_to_camelcase(file_name);
            break;
        case IDLOptions::kPascalCase:
            case_name = generator::underscores_to_pascalcase(file_name);
            break;
        }
        return fmt::format("{}/{}{}", path, case_name, extension);
    }

private:
    void generate_ki_func(const Type &type)
    {
        for (auto &&field : type.obj_def->fields.vec)
        {
            if (field->is_key)
            {
                code_ += generate_key_func(field->name);
            }
            else if (field->is_index)
            {
                code_ += generate_index_func(field->name);
            }
        }
    }

    void generate_ki_map(const Type &type)
    {
        for (auto &&field : type.obj_def->fields.vec)
        {
            if (field->is_key)
            {
                code_ += generate_key_map(field->name);
            }
            else if (field->is_index)
            {
                code_ += generate_index_map(field->name);
            }
        }
    }

    std::string generate_key_func(const std::string &field_name)
    {
        std::string code;
        auto lower_case = boost::algorithm::to_lower_copy(field_name);
        auto pascal_case = generator::underscores_to_pascalcase(field_name);
        code += fmt::format("\nM[\"table_{}_key\"] = {{}}\n\n", lower_case);
        code += fmt::format("function M.get{}ByKey(key)\n", pascal_case);
        code += fmt::format("\treturn M[\"table_{}_key\"][key]\n", lower_case);
        code += "end\n";
        return code;
    }

    std::string generate_key_map(const std::string &field_name)
    {
        std::string code;
        auto lower_case = boost::algorithm::to_lower_copy(field_name);
        code += "for k, v in pairs(M[\"table\"]) do\n";
        code += fmt::format("\tlocal id = v[\"{}\"]\n", field_name);
        code += fmt::format("\tM[\"table_{}_key\"][id] = v\n", lower_case);
        code += "end\n";
        return code;
    }

    std::string generate_index_func(const std::string &field_name)
    {
        std::string code;
        auto lower_case = boost::algorithm::to_lower_copy(field_name);
        auto pascal_case = generator::underscores_to_pascalcase(field_name);
        code += fmt::format("\nM[\"table_{}_index\"] = {{}}\n\n", lower_case);
        code += fmt::format("function M.get{}ByIndex(index)\n", pascal_case);
        code += fmt::format("\treturn M[\"table_{}_index\"][index]\n", lower_case);
        code += "end\n";
        return code;
    }

    std::string generate_index_map(const std::string &field_name)
    {
        std::string code;
        auto lower_case = boost::algorithm::to_lower_copy(field_name);
        code += "for k, v in pairs(M[\"table\"]) do\n";
        code += fmt::format("\tlocal id = v[\"{}\"]\n", field_name);
        code += fmt::format("\tif M[\"table_{}_index\"][id] == nil then\n", lower_case);
        code += fmt::format("\t\tM[\"table_{}_index\"][id] = {{}}\n", lower_case);
        code += "\tend\n";
        code += fmt::format("\ttable.insert(M[\"table_{}_index\"][id], v)\n", lower_case);
        code += "end\n";
        return code;
    }

    CodeWriter code_;
};

bool generate_lua(Model &model, const IDLOptions &opts, const std::string &path,
    const std::string &file_name)
{
    LuaGenerator generator(model, opts, path, file_name);
    return generator.generate();
}

} // namespace core
} // namespace kr
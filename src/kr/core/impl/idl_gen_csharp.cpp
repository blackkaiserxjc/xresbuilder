#include <algorithm>
#include <filesystem>
#include <unordered_map>

#include <fmt/format.h>

#include <kr/core/code_generator.h>
#include <kr/core/generator_helpers.h>
#include <kr/core/idl.h>
#include <kr/utility/utility.h>

namespace kr {
namespace core {

class CSharpGenerator : public CodeGenerator
{
public:
    CSharpGenerator(Model &model, const IDLOptions &opts, const std::string &path,
        const std::string &file_name)
        : CodeGenerator(model, opts, path, file_name), root_ns_("ETModel.Config"), pod_depth_(0), obj_depth_(0)
    {
        code_.indent();
    }

    ~CSharpGenerator()
    {
        code_.outdent();
    }

    bool generate() override
    {
        code_.clear();
        pod_depth_ = 0;
        obj_depth_ = 0;
        auto table_def = model_.type();
        assert(table_def.base_type == BASE_TYPE_OBJECT);
        auto class_name = generator::underscores_to_pascalcase(file_name_);
        auto name_space = gen_namespace();
        gen_categories(class_name);
        gen_object(table_def, class_name);
        return save_type(name_space, code_.to_string());
    }

    std::string generated_filename(const std::string &path,
        const std::string &file_name) override
    {
        std::string extension = ".cs";
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
    std::string get_type_basic(const Type &type) const
    {
        static std::unordered_map<uint32_t, const char *> csharp_typenames = {
            {BASE_TYPE_NONE, nullptr},
            {BASE_TYPE_BOOL, "bool"},
            {BASE_TYPE_INT, "int"},
            {BASE_TYPE_LONG, "long"},
            {BASE_TYPE_FLOAT, "float"},
            {BASE_TYPE_STRING, "string"}};
        return csharp_typenames[type.base_type];
    }

    void gen_categories(const std::string &name)
    {
        code_ +=
            "[Config((int)(AppType.ClientH | AppType.ClientM | AppType.Gate | "
            "AppType.Map))]";
        code_ +=
            fmt::format("public partial class {0}Category : ACategory<{0}>", name);
        code_ += "{";
        code_ += "}\n";
    };

    void gen_object(const Type &type, const std::string &name)
    {
        if (!obj_depth_)
        {
            code_ += fmt::format("public class {}: IConfig", name);
        }
        else
        {
            code_ += fmt::format("public class {}", name);
        }
        obj_depth_++;
        code_ += "{";
        code_.indent();
        for (auto &&field : type.obj_def->fields.vec)
        {
            auto field_type = field->value.type;
            auto field_name = field->name;
            auto field_index = field->index;
            if (IsPod(field_type.base_type))
            {
                gen_pod(field_type, field_name, field_index);
            }
            else if (IsObject(field_type.base_type))
            {
                gen_object(field_type, field_name);
            }
            else if (IsArray(field_type.base_type))
            {
                gen_array(field_type, field_name);
            }
        }
        code_.outdent();
        code_ += "}";
    }

    void gen_pod(const Type &type, const std::string &name,
        uint32_t field_index)
    {
        if (!pod_depth_ && !field_index)
        {
            code_ += fmt::format("public {} {} {{get; set;}}", get_type_basic(type), name);
        }
        else
        {
            code_ += fmt::format("public {} {};", get_type_basic(type), name);
        }
        pod_depth_++;
    }

    void gen_array(const Type &type, const std::string &name)
    {
        if (IsPod(type.element))
        {
            Type element(type.element);
            code_ += fmt::format("public List<{0}> {1} = new List<{0}>();",
                get_type_basic(element), name);
        }
        else if (IsObject(type.element))
        {
            Type element(type.element, type.obj_def);
            auto class_name = generator::underscores_to_pascalcase(name);
            gen_object(element, class_name);
            code_ += fmt::format("public List<{0}> {1} = new List<{0}>();",
                class_name, name);
        }
    }

    std::string gen_namespace()
    {
        std::vector<std::string> results{root_ns_};
        auto relative_path = std::filesystem::relative(path_, opts_.dest);
        for (auto &e : relative_path)
        {
            auto value = generator::underscores_to_pascalcase(e.string());
            if (!value.empty() && std::all_of(value.begin(), value.end(), [](auto &&ch) {
                    return std::isalpha(ch, std::locale::classic());
                }))
            {
                results.emplace_back(value);
            }
        }
        return fmt::format("{}", fmt::join(results, "."));
    }

    bool save_type(const std::string &namespace_name,
        const std::string &class_code)
    {
        if (!class_code.length())
        {
            return true;
        }

        std::string code =
            "// <auto-generated> \n"
            "// "
            + std::string(generated_warning()) +
            "\n"
            "// </auto-generated>\n\n";

        code += "using System.Collections.Generic;\n";
        if (!namespace_name.empty())
        {
            code += "namespace " + namespace_name + "\n{\n";
        }

        code += class_code;
        if (!namespace_name.empty())
        {
            code += "\n}\n";
        }

        auto file_path = generated_filename(path_, file_name_);
        return kr::utility::save_file(file_path.c_str(), code, false);
    }

    int pod_depth_;
    int obj_depth_;
    std::string root_ns_;
    CodeWriter code_;
};

bool generate_csharp(Model &model, const IDLOptions &opts,
    const std::string &path, const std::string &file_name)
{
    CSharpGenerator generator(model, opts, path, file_name);
    return generator.generate();
}

} // namespace core
} // namespace kr

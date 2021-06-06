#pragma once

#include <string>

namespace kr {
namespace core {

class Model;

struct IDLOptions {
    enum Language
    {
        kLua = 1 << 0,
        kJson = 1 << 1,
        kCSharp = 1 << 2,
        kMax
    };
    enum NamingStyle
    {
        kCamelCase = 1 << 0,
        kPascalCase = 1 << 1,
        kMaxRules,
    };

    IDLOptions()
        : src{}, dest{}, extension{}, filename_naming_style{},
          field_naming_style{}, indent_step{2} {}

    std::string src;
    std::string dest;
    std::string extension;
    std::uint32_t lang_to_generate;
    std::uint32_t filename_naming_style;
    std::uint32_t field_naming_style;
    std::uint32_t indent_step;
};

extern bool generate_json(Model& model, const IDLOptions& opts, const std::string& path, const std::string& file_name);

extern bool generate_lua(Model& model,  const IDLOptions& opts, const std::string& path, const std::string& file_name);

extern bool generate_csharp(Model& model, const IDLOptions& opts, const std::string& path, const std::string& file_name);

} // namespace core
} // namespace kr
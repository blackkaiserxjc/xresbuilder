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
        kMax
    };
    enum NamingStyle
    {
        kDefault = 0,
        kCamelCase = 1 << 0,
        kPascalCase = 1 << 1,
        kMaxRules,
    };
    std::string src;
    std::string dest;
    std::uint32_t lang_to_generate;
    NamingStyle file_naming_style;
    NamingStyle field_naming_style;
};

extern bool generate_json(Model& model, const IDLOptions& opts, const std::string& path, const std::string& file_name);

extern bool generate_lua(Model& model,  const IDLOptions& opts, const std::string& path, const std::string& file_name);

} // namespace core
} // namespace kr
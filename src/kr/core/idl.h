#pragma once

#include <string>
#include <vector>

namespace kr {
namespace core {

class Model;

struct IDLOptions {
  enum Language { kLua = 1 << 0, kJson = 1 << 1, kCSharp = 2 << 1, kMax };
  enum NamingStyle {
    kCamelCase = 1 << 0,
    kPascalCase = 1 << 1,
    kMaxRules,
  };

  IDLOptions()
      : src{}, dest{}, extension{}, lang_to_generate{}, filename_naming_style{},
        field_naming_style{}, indent_step{2}, src_paths_{} {}

  std::string src;
  std::string dest;
  std::string extension;
  std::uint32_t lang_to_generate;
  std::uint32_t filename_naming_style;
  std::uint32_t field_naming_style;
  std::uint32_t indent_step;
  std::vector<std::string> src_paths_;
};

extern bool generate_json(Model &model, const IDLOptions &opts,
                          const std::string &path,
                          const std::string &file_name);

extern bool generate_lua(Model &model, const IDLOptions &opts,
                         const std::string &path, const std::string &file_name);

extern bool generate_csharp(Model &model, const IDLOptions &opts,
                            const std::string &path,
                            const std::string &file_name);

} // namespace core
} // namespace kr
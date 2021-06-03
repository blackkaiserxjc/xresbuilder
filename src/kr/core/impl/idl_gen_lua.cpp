#include <locale>
#include <string>
#include <fmt/format.h>

#include <kr/core/code_generator.h>
#include <kr/core/generator_helpers.h>
#include <kr/core/idl.h>
#include <kr/utility/utility.h>

namespace kr {
namespace core {

struct LuaVisitor : public msgpack::null_visitor {
  LuaVisitor(CodeWriter &writer, uint32_t field_name_case) : writer_(writer), field_name_case_(field_name_case) {}

  bool visit_null() {
    writer_ += "nil";
    return true;
  }

  bool visit_boolean(bool v) {
    if (v) {
      writer_ += "true";
    } else {
      writer_ += "false";
    }
    return true;
  }

  bool visit_positive_integer(uint64_t v) {
    writer_ += std::to_string(v);
    return true;
  }

  bool visit_negative_integer(int64_t v) {
    writer_ += std::to_string(v);
    return true;
  }

  bool visit_float32(float v) {
    writer_ += std::to_string(v);
    return true;
  }

  bool visit_float64(double v) {
    writer_ += std::to_string(v);
    return true;
  }

  bool visit_str(const char *v, uint32_t size) {
    auto key = std::string(v, size);
    if (is_map_key) {
      key = to_case_name(key);
    }
    writer_ += fmt::format("\"{}\"", key);
    return true;
  }

  bool start_array(uint32_t num_elements) {
    current_size_.emplace_back(0, num_elements);
    writer_.indent();
    writer_ += "{";
    return true;
  }

  bool start_array_item() {
    auto &&[index, size] = current_size_.back();
    index++;
    writer_.write_indent();
    writer_ += fmt::format("[{}] = ", index);
    return true;
  }

  bool end_array_item() {
    writer_ += ",";
    return true;
  }

  bool end_array() {
    current_size_.pop_back();
    writer_.unindent();
    writer_.write_indent();
    writer_ += "}";
    return true;
  }

  bool start_map(uint32_t num_kv_pairs) {
    current_size_.emplace_back(0, num_kv_pairs);
    writer_.indent();
    writer_ += "{";
    return true;
  }

  bool start_map_key() {
    writer_.write_indent();
    writer_ += "[";
    is_map_key = true;
    return true;
  }

  bool end_map_key() {
    writer_ += "] = ";
    is_map_key = false;
    return true;
  }

  bool start_map_value() { return true; }

  bool end_map_value() {
    writer_ += ",";
    return true;
  }

  bool end_map() {
    current_size_.pop_back();
    writer_.unindent();
    writer_.write_indent();
    writer_ += "}";
    return true;
  }

private:
    std::string to_case_name(const std::string& input) {
    if (field_name_case_ == IDLOptions::NamingStyle::kCamelCase) {
      return generator::underscores_to_camelcase(input);
    } else if (field_name_case_ == IDLOptions::NamingStyle::kPascalCase) {
      return generator::underscores_to_pascalcase(input);
    } else {
      return input;
    }
  }

  CodeWriter &writer_;
  uint32_t depath_;
  std::vector<std::tuple<uint32_t, uint32_t>> current_size_;
  uint32_t field_name_case_;
  bool is_map_key;
};

class LuaGenerator : public CodeGenerator {
public:
  LuaGenerator(Model &model, const IDLOptions& opts, const std::string &path,
               const std::string &file_name)
      : CodeGenerator(model, opts, path, file_name) {}
  ~LuaGenerator() {}

  bool generate() override {
    code_.clear();
    msgpack::sbuffer buffer;
    Packer<msgpack::packer<msgpack::sbuffer>> packer{buffer};
    model_.serialize(packer);

    code_ += "local M = ";

    std::size_t offset = 0;
    LuaVisitor visitor(code_, opts_.field_naming_style);
    msgpack::parse(buffer.data(), buffer.size(), offset, visitor);

    code_ += "\n";
    code_ += "return M";

    const std::string file_path = generated_filename(path_, file_name_);
    const std::string final_code = code_.to_string();
    return kr::utility::save_file(file_path.c_str(), final_code, false);
  }

  std::string generated_filename(const std::string &path,
                                 const std::string &file_name) override {

    std::string extension = ".lua";
    if (!opts_.extension.empty()) {
      extension = opts_.extension;
    }
    auto case_name = file_name;
    switch (opts_.filename_naming_style) {
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
  CodeWriter code_;
};

bool generate_lua(Model &model, const IDLOptions& opts, const std::string &path,
                  const std::string &file_name) {
  LuaGenerator generator(model, opts, path, file_name);
  return generator.generate();
}

} // namespace core
} // namespace kr
#include <locale>
#include <string>
#include <fmt/format.h>

#include <kr/core/code_generator.h>
#include <kr/core/idl.h>
#include <kr/utility/utility.h>

namespace kr {
namespace core {

struct LuaVisitor : public msgpack::null_visitor {
  LuaVisitor(CodeWriter &writer) : writer_(writer) {}

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
    writer_ += '"' + std::string(v, size) + '"';
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
    return true;
  }

  bool end_map_key() {
    writer_ += "] = ";
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
  CodeWriter &writer_;
  uint32_t depath_;
  std::vector<std::tuple<uint32_t, uint32_t>> current_size_;
};

class LuaGenerator : public CodeGenerator {
public:
  LuaGenerator(Model &model, const std::string &path,
               const std::string &file_name)
      : CodeGenerator(model, path, file_name) {}
  ~LuaGenerator() {}

  bool generate() override {
    code_.clear();
    msgpack::sbuffer buffer;
    Packer<msgpack::packer<msgpack::sbuffer>> packer{buffer};
    model_.serialize(packer);

    code_ += "local M = ";

    std::size_t offset = 0;
    LuaVisitor visitor(code_);
    msgpack::parse(buffer.data(), buffer.size(), offset, visitor);

    code_ += "\n";
    code_ += "return M";

    const std::string file_path = generated_filename(path_, file_name_);
    const std::string final_code = code_.to_string();
    return kr::utility::save_file(file_path.c_str(), final_code, false);
  }

  std::string generated_filename(const std::string &path,
                                 const std::string &file_name) override {
    
    return fmt::format("{}/{}.lua", path, file_name);
  }

private:
  CodeWriter code_;
};

bool generate_lua(Model &model, const std::string &path,
                  const std::string &file_name) {
  LuaGenerator generator(model, path, file_name);
  return generator.generate();
}

} // namespace core
} // namespace kr
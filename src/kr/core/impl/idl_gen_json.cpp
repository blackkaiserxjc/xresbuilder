#include <iostream>
#include <locale>

#include <fmt/format.h>

#include <kr/core/code_generator.h>
#include <kr/core/idl.h>
#include <kr/utility/utility.h>

namespace kr {
namespace core {

static std::string pascal_case_name(const std::string &name,
                                    bool is_first_upper = true) {
  std::string case_name;
  if (name.front() != '_') {
    auto ch = is_first_upper
                  ? std::toupper(name.front(), std::locale::classic())
                  : std::tolower(name.front(), std::locale::classic());
    case_name.push_back(ch);
  }

  for (size_t i = 1; i < name.size(); ++i) {
    if (name[i] != '_') {
      if (!std::isalpha(name[i - 1], std::locale::classic())) {
        case_name.push_back(std::toupper(name[i], std::locale::classic()));
      } else {
        case_name.push_back(name[i]);
      }
    }
  }
  return case_name;
}

class JsonVisitor : public msgpack::null_visitor {
public:
  JsonVisitor(CodeWriter &writer)
      : writer_(writer), is_map_key(false), array_depth_(0), map_depth_(0) {}

  bool visit_nil() {
    writer_ += "null";
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
      //key = pascal_case_name(key, false);
    }
    writer_ += fmt::format("\"{}\"", key);
    return true;
  }

  bool start_array(uint32_t num_elements) {
    current_size_.push_back(num_elements);
    if (array_depth_ > 0) {
      writer_ += "[";
    }
    ++array_depth_;
    return true;
  }

  bool end_array_item() {
    --current_size_.back();
    if (current_size_.back() != 0 && current_size_.size() > 1) {
      writer_ += ",";
    }
    return true;
  }

  bool end_array() {
    --array_depth_;
    if (array_depth_ > 0) {
      writer_ += "]";
    }
    current_size_.pop_back();
    return true;
  }

  bool start_map(uint32_t num_kv_pairs) {
    current_size_.push_back(num_kv_pairs);
    writer_ += "{";
    ++map_depth_;
    return true;
  }

  bool start_map_key() {
    is_map_key = true;
    return true;
  }

  bool end_map_key() {
    writer_ += ":";
    is_map_key = false;
    return true;
  }

  bool end_map_value() {
    --current_size_.back();
    if (current_size_.back() != 0) {
      writer_ += ",";
    }
    return true;
  }

  bool end_map() {
    --map_depth_;
    current_size_.pop_back();
    writer_ += "}";
    if (map_depth_ == 0) {
      writer_ += "\n";
    }
    return true;
  }

private:
  bool is_map_key;
  int array_depth_;
  int map_depth_;
  CodeWriter &writer_;
  std::vector<uint32_t> current_size_;
};

class JsonGenerator : public CodeGenerator {
public:
  JsonGenerator(Model &model, const std::string &path,
                const std::string &file_name)
      : CodeGenerator(model, path, file_name) {}

  ~JsonGenerator() {}

  bool generate() override {
    code_.clear();
    msgpack::sbuffer buffer;
    Packer<msgpack::packer<msgpack::sbuffer>> packer{buffer};
    model_.serialize(packer);

    std::size_t offset = 0;
    JsonVisitor visitor(code_);
    msgpack::parse(buffer.data(), buffer.size(), offset, visitor);

    const std::string file_path = generated_filename(path_, file_name_);
    const std::string final_code = code_.to_string();
    return kr::utility::save_file(file_path.c_str(), final_code, false);
  }

  std::string generated_filename(const std::string &path,
                                 const std::string &file_name) override {

    return fmt::format("{}/{}.txt", path, pascal_case_name(file_name));
  }

private:
  CodeWriter code_;
};

bool generate_json(Model &model, const IDLOptions& opts, const std::string &path,
                   const std::string &file_name) {
  JsonGenerator generator(model, path, file_name);
  return generator.generate();
}

} // namespace core
} // namespace kr
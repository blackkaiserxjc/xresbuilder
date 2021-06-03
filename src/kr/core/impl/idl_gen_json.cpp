#include <iostream>
#include <locale>

#include <fmt/format.h>

#include <kr/core/code_generator.h>
#include <kr/core/generator_helpers.h>
#include <kr/core/idl.h>
#include <kr/utility/utility.h>

namespace kr {
namespace core {

class JsonVisitor : public msgpack::null_visitor {
public:
  JsonVisitor(CodeWriter &writer, uint32_t field_name_case)
      : writer_(writer), field_name_case_(field_name_case), is_map_key(false), array_depth_(0), map_depth_(0) {}

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
      key = to_case_name(key);
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
  std::string to_case_name(const std::string& input) {
    if (field_name_case_ == IDLOptions::NamingStyle::kCamelCase) {
      return generator::underscores_to_camelcase(input);
    } else if (field_name_case_ == IDLOptions::NamingStyle::kPascalCase) {
      return generator::underscores_to_pascalcase(input);
    } else {
      return input;
    }
  }

  bool is_map_key;
  int array_depth_;
  int map_depth_;
  CodeWriter &writer_;
  std::vector<uint32_t> current_size_;  
  uint32_t field_name_case_;
  std::string extension_;
};

class JsonGenerator : public CodeGenerator {
public:
  JsonGenerator(Model &model, const IDLOptions& opts, const std::string & path,
                const std::string &file_name)
      : CodeGenerator(model, opts, path, file_name) {}

  ~JsonGenerator() {}

  bool generate() override {
    code_.clear();
    msgpack::sbuffer buffer;
    Packer<msgpack::packer<msgpack::sbuffer>> packer{buffer};
    model_.serialize(packer);

    std::size_t offset = 0;
    JsonVisitor visitor(code_, opts_.field_naming_style);
    msgpack::parse(buffer.data(), buffer.size(), offset, visitor);

    const std::string file_path = generated_filename(path_, file_name_);
    const std::string final_code = code_.to_string();
    return kr::utility::save_file(file_path.c_str(), final_code, false);
  }

  std::string generated_filename(const std::string &path,
                                 const std::string &file_name) override {
    std::string extension = ".txt";
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

bool generate_json(Model &model, const IDLOptions &opts, const std::string &path,
                  const std::string &file_name) {
  JsonGenerator generator(model, opts, path, file_name);
  return generator.generate();
}

} // namespace core
} // namespace kr
#pragma once

#include <sstream>
#include <string>
#include <unordered_map>

#include <boost/core/noncopyable.hpp>

#include <kr/core/model.h>

namespace kr {
namespace core {

class CodeWriter {
public:
  CodeWriter(const std::string &indent = "\t") : indent_(indent) {}

  void clear() {
    value_map_.clear();
    stream_.str("");
  }

  void set_value(const std::string &key, const std::string &value) {
    value_map_[key] = value;
  }

  std::string value(const std::string &key) const {
    auto iter = value_map_.find(key);
    return iter != value_map_.end() ? iter->second : "";
  }

  void indent();
  void unindent();
  void write_indent();

  void operator+=(std::string text);
  std::string to_string() const { return stream_.str(); };

private:
  std::unordered_map<std::string, std::string> value_map_;
  std::stringstream stream_;
  std::string indent_;
  std::string indent_string_;
};

class Model;
class IDLOptions;
class CodeGenerator : private boost::noncopyable {
public:
  CodeGenerator(Model &model, const IDLOptions& opts, const std::string& path, const std::string& file_name)
      : model_{model}, opts_{opts}, path_{path}, file_name_{file_name} {}

  virtual ~CodeGenerator(){}

  virtual bool generate() = 0;
  virtual std::string generated_filename(const std::string &path,
                                         const std::string &file_name) = 0;
  const char* generated_warning();
protected:
  Model &model_;
  const IDLOptions& opts_;
  std::string path_;
  std::string file_name_;
};

} // namespace core
} // namespace kr

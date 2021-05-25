#ifndef KR_APP_CORE_CODE_GENERATOR_H_
#define KR_APP_CORE_CODE_GENERATOR_H_

#include <sstream>
#include <string>
#include <unordered_map>

#include <boost/core/noncopyable.hpp>

namespace kr {
namespace core {

class CodeWriter {
public:
  CodeWriter() = default;

  void Clear() {
    value_map_.clear();
    stream_.str("");
  }

  void SetValue(const std::string &key, const std::string &value) {
    value_map_[key] = value;
  }

  void operator+=(std::string text);
  std::string ToString() const { return stream_.str(); };

private:
  std::unordered_map<std::string, std::string> value_map_;
  std::stringstream stream_;
};

class CodeGenerator : private boost::noncopyable {
public:
  CodeGenerator(const std::string &path, const std::string &file_name)
      : path_{path}, file_name_{file_name} {}
  virtual ~CodeGenerator(){};

  virtual bool Generate() = 0;
private:
  const std::string &path_;
  const std::string &file_name_;
};

} // namespace core
} // namespace kr

#endif /* KR_APP_CORE_CODE_GENERATOR_ */
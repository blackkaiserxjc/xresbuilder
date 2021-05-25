#ifndef KR_APP_CORE_IDL_H_
#define KR_APP_CORE_IDL_H_

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "type.h"
#include "object_pack.h"

namespace kr {
namespace core {

/** 解析器 */
class Parser {
public:
  Parser() = default;
  ~Parser() = default;

  Parser(const Parser &) = delete;
  Parser &operator=(const Parser &) = delete;

  bool Parse(const std::string &field, const std::string& cell);
  bool ParseField(const std::string& source);
  msgpack::object ParseCell(const std::string &source);
  Type Message() const;

protected:
  Type type_;
};
} // namespace core
} // namespace kr

#endif /* KR_APP_CORE_IDL_H_ */
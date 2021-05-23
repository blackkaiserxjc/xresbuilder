#ifndef KR_APP_CORE_IDL_H_
#define KR_APP_CORE_IDL_H_

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "types.h"

/** 解析结构 */
namespace kr {
namespace core {

struct FieldDef;
struct ObjectDef;
struct Type {
  explicit Type(BaseType base_type = BASE_TYPE_NONE,
                std::shared_ptr<ObjectDef> obj_def = nullptr,
                std::uint16_t fixed_length = 0)
      : base_type(base_type), 
        element(BASE_TYPE_NONE), 
        obj_def(obj_def),
        fixed_length(fixed_length) {}

  bool operator==(const Type &t) {
    return base_type == t.base_type && element == t.element &&
           obj_def.get() == t.obj_def.get();
  }

  BaseType base_type;
  BaseType element;
  std::shared_ptr<ObjectDef> obj_def;
  uint16_t fixed_length;
};

struct Value {
  Value() : constant("0"), offset(0) {}
  Type type;
  std::string constant;
  std::uint16_t offset;
};

/** 符号表 */
template <class T> class SymbolTable {
public:
  SymbolTable() = default;
  ~SymbolTable() = default;

  bool Add(const std::string &name, std::shared_ptr<T> element) {
    vec.emplace_back(element);
    if (auto iter = dict.find(name); iter != dict.end()) {
      return true;
    }
    dict[name] = element;
    return false;
  }

  std::shared_ptr<T> Lookup(const std::string &name) const {
    auto iter = dict.find(name);
    return iter == dict.end() ? nullptr : iter->second;
  }

public:
  std::unordered_map<std::string, std::shared_ptr<T>> dict;
  std::vector<std::shared_ptr<T>> vec;
};

/** field, object 基类*/
struct Definition {
  Definition() : name{}, index{-1} {}

  int index;
  std::string name;
};

struct FieldDef : public Definition {
  FieldDef() : key(false) {}

  Value value;
  bool key;
};

struct ObjectDef : public Definition {
  SymbolTable<FieldDef> fields;
};

/** 解析器 */
class Parser {
public:
  Parser() = default;
  ~Parser() = default;

  Parser(const Parser &) = delete;
  Parser &operator=(const Parser &) = delete;

  bool Parse(const std::string &source);
  bool ParseCell(const std::string &source);
  Type Message() const;

protected:
  Type type_;
};
} // namespace core
} // namespace kr

#endif /* KR_APP_CORE_IDL_H_ */
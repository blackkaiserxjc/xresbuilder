#ifndef KR_APP_CORE_TYPE_H_
#define KR_APP_CORE_TYPE_H_

namespace kr {
namespace core {
/** 数据类型 */
enum BaseType {
  BASE_TYPE_NONE = 0,
  BASE_TYPE_BOOL = 1,
  BASE_TYPE_INT = 2,
  BASE_TYPE_FLOAT = 3,
  BASE_TYPE_STRING = 4,
  BASE_TYPE_ARRAY = 5,
  BASE_TYPE_OBJECT = 6
};

inline bool IsPod(BaseType type) {
  return type >= BASE_TYPE_BOOL && type <= BASE_TYPE_STRING;
};
inline bool IsBool(BaseType type) { return type == BASE_TYPE_BOOL; }
inline bool IsInt(BaseType type) { return type == BASE_TYPE_INT; }
inline bool IsFloat(BaseType type) { return type == BASE_TYPE_FLOAT; }
inline bool IsString(BaseType type) { return type == BASE_TYPE_STRING; }
inline bool IsArray(BaseType type) { return type == BASE_TYPE_ARRAY; }
inline bool IsObject(BaseType type) { return type == BASE_TYPE_OBJECT; };

struct FieldDef;
struct ObjectDef;
struct Type {
  explicit Type(BaseType base_type = BASE_TYPE_NONE,
                std::shared_ptr<ObjectDef> obj_def = nullptr,
                std::uint16_t fixed_length = 0)
      : base_type(base_type), element(BASE_TYPE_NONE), obj_def(obj_def),
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

  std::size_t Size() const { return dict.size(); }

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

} // namespace core
} // namespace kr

#endif
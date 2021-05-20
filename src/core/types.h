#ifndef KR_APP_CORE_TYPES_H_
#define KR_APP_CORE_TYPES_H_

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

} // namespace core
} // namespace kr

#endif
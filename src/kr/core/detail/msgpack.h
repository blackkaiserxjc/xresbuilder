#pragma once

#include <msgpack.hpp>

namespace kr {
namespace core {

template <typename Stream> struct Packer<::msgpack::packer<Stream>> {
public:
  explicit Packer(Stream &stream) : packer_(stream) {}

  Packer &pack(bool value) {
    if (value) {
      packer_.pack_true();
    } else {
      packer_.pack_false();
    }
    return *this;
  }

  Packer &pack(std::int32_t value) {
    packer_.pack_int32(value);
    return *this;
  }

  Packer &pack(std::uint32_t value) {
    packer_.pack_uint32(value);
    return *this;
  }

  Packer &pack(std::int64_t value) {
    packer_.pack_int64(value);
    return *this;
  }

  Packer &pack(std::uint64_t value) {
    packer_.pack_uint64(value);
    return *this;
  }

  Packer &pack(double value) {
    packer_.pack_double(value);
    return *this;
  }

  Packer &pack(std::string_view value) {
    packer_.pack_str(static_cast<std::uint32_t>(value.size()));
    packer_.pack_str_body(value.data(),
                          static_cast<std::uint32_t>(value.size()));
    return *this;
  }

  template <typename T> Packer &key(T value) {
    pack(value);
    return *this;
  }

  template <typename T> Packer &kv(std::string_view key, T value) {
    pack(key);
    pack(value);
    return *this;
  }

  Packer &pack_begin_array(std::string_view name, std::size_t size) {
    pack(name);
    packer_.pack_array(size);
    return *this;
  }

  Packer &pack_begin_array(std::size_t size) {
    packer_.pack_array(size);
    return *this;
  }

  Packer &pack_end_array() { return *this; }

  Packer &pack_begin_map(std::string_view name, std::size_t size) {
    pack(name);
    packer_.pack_map(size);
    return *this;
  }

  Packer &pack_begin_map(std::size_t size) {
    packer_.pack_map(size);
    return *this;
  }

  Packer &pack_end_map() { return *this; }

private:
  ::msgpack::packer<Stream> packer_;
};

template <> struct UnPacker<::msgpack::object> {
public:
  explicit UnPacker(const ::msgpack::object &object) : object_{object} {}

  BaseType type() const {
    switch (object_.type) {
    case ::msgpack::type::NIL:
      return BASE_TYPE_NONE;
    case ::msgpack::type::BOOLEAN:
      return BASE_TYPE_BOOL;
    case ::msgpack::type::POSITIVE_INTEGER:
    case ::msgpack::type::NEGATIVE_INTEGER:
      return BASE_TYPE_INT;
    case ::msgpack::type::FLOAT32:
    case ::msgpack::type::FLOAT64:
      return BASE_TYPE_FLOAT;
    case ::msgpack::type::STR:
    case ::msgpack::type::BIN:
    case ::msgpack::type::EXT:
      return BASE_TYPE_STRING;
    case ::msgpack::type::ARRAY:
      return BASE_TYPE_ARRAY;
    case ::msgpack::type::MAP:
      return BASE_TYPE_OBJECT;
    default:
      assert("unknow type");
      return BASE_TYPE_NONE;
    }
  }

  template <typename T> T as() const {
    if constexpr (std::is_same_v<T, bool>) {
      return object_.via.boolean;
    } else if constexpr (std::is_same_v<T, std::int32_t>) {
      return static_cast<std::int32_t>(object_.via.i64);
    } else if constexpr (std::is_same_v<T, std::uint32_t>) {
      return static_cast<std::uint32_t>(object_.via.u64);
    } else if constexpr (std::is_same_v<T, std::int64_t>) {
      return object_.via.i64;
    } else if constexpr (std::is_same_v<T, std::uint64_t>) {
      return object_.via.u64;
    } else if constexpr (std::is_same_v<T, double>) {
      return object_.via.f64;
    } else if constexpr (std::is_same_v<T, std::string_view>) {
      return std::string_view(object_.via.str.ptr, object_.via.str.size);
    }
  }

  template <typename T, typename Action, typename Except>
  void to(Action &&action, Except &&except) const {
    if constexpr (std::is_same_v<T, bool>) {
      switch (object_.type) {
      case ::msgpack::type::BOOLEAN:
        action(object_.via.boolean);
        break;
      case ::msgpack::type::POSITIVE_INTEGER:
        action(object_.via.u64 != 0);
        break;
      case ::msgpack::type::NEGATIVE_INTEGER:
        action(object_.via.i64 != 0);
        break;
      case ::msgpack::type::FLOAT32:
      case ::msgpack::type::FLOAT64:
        action(object_.via.f64 != 0);
        break;
      default:
        except();
        break;
      }
    } else if constexpr (std::is_same_v<T, std::int32_t>) {
      switch (object_.type) {
      case ::msgpack::type::BOOLEAN:
        action(object_.via.boolean ? 1 : 0);
        break;
      case ::msgpack::type::POSITIVE_INTEGER:
        action(static_cast<std::int32_t>(object_.via.u64));
        break;
      case ::msgpack::type::NEGATIVE_INTEGER:
        action(static_cast<std::int32_t>(object_.via.i64));
        break;
      case ::msgpack::type::FLOAT32:
      case ::msgpack::type::FLOAT64:
        action(static_cast<std::int32_t>(object_.via.f64));
        break;
      }
    } else if constexpr (std::is_same_v<T, std::uint32_t>) {
      switch (object_.type) {
      case ::msgpack::type::BOOLEAN:
        action(object_.via.boolean ? 1 : 0);
        break;
      case ::msgpack::type::POSITIVE_INTEGER:
        action(static_cast<std::uint32_t>(object_.via.u64));
        break;
      case ::msgpack::type::NEGATIVE_INTEGER:
        action(static_cast<std::uint32_t>(object_.via.i64));
        break;
      case ::msgpack::type::FLOAT32:
      case ::msgpack::type::FLOAT64:
        action(static_cast<std::uint32_t>(object_.via.f64));
        break;
      }
    } else if constexpr (std::is_same_v<T, std::int64_t>) {
      switch (object_.type) {
      case ::msgpack::type::BOOLEAN:
        action(object_.via.boolean ? 1 : 0);
        break;
      case ::msgpack::type::POSITIVE_INTEGER:
        action(static_cast<std::int64_t>(object_.via.u64));
        break;
      case ::msgpack::type::NEGATIVE_INTEGER:
        action(static_cast<std::int64_t>(object_.via.i64));
        break;
      case ::msgpack::type::FLOAT32:
      case ::msgpack::type::FLOAT64:
        action(static_cast<std::int64_t>(object_.via.f64));
        break;
      }
    } else if constexpr (std::is_same_v<T, std::uint64_t>) {
      switch (object_.type) {
      case ::msgpack::type::BOOLEAN:
        action(object_.via.boolean ? 1 : 0);
        break;
      case ::msgpack::type::POSITIVE_INTEGER:
        action(static_cast<std::uint64_t>(object_.via.u64));
        break;
      case ::msgpack::type::NEGATIVE_INTEGER:
        action(static_cast<std::uint64_t>(object_.via.i64));
        break;
      case ::msgpack::type::FLOAT32:
      case ::msgpack::type::FLOAT64:
        action(static_cast<std::uint64_t>(object_.via.f64));
        break;
      }
    } else if constexpr (std::is_same_v<T, double>) {
      switch (object_.type) {
      case ::msgpack::type::BOOLEAN:
        action(static_cast<double>(object_.via.boolean ? 1 : 0));
        break;
      case ::msgpack::type::POSITIVE_INTEGER:
        action(static_cast<double>(object_.via.u64));
        break;
      case ::msgpack::type::NEGATIVE_INTEGER:
        action(static_cast<double>(object_.via.i64));
        break;
      case ::msgpack::type::FLOAT32:
      case ::msgpack::type::FLOAT64:
        action(static_cast<double>(object_.via.f64));
        break;
      }
    } else if constexpr (std::is_same_v<T, std::string_view>) {
      switch (object_.type) {
      case ::msgpack::type::STR:
      case ::msgpack::type::BIN:
      case ::msgpack::type::EXT:
        action(std::string_view(object_.via.str.ptr, object_.via.str.size));
        break;
      }
    }
  }

  template <typename Action> void visit_begin_array(Action &&action) const {
    assert(object_.type == ::msgpack::type::ARRAY);
    action(object_.via.array.size);
  }

  template <typename Init, typename Action>
  void visit_array(Init &&init, Action &&action) const {
    assert(object_.type == ::msgpack::type::ARRAY);
    init(object_.via.array.size);
    for (std::size_t index = 0; index != object_.via.array.size; index++) {
      action(index, UnPacker((object_.via.array.ptr[index])));
    }
  }

  template <typename Action> void visit_map(Action &&action) const {
    assert(object_.type == ::msgpack::type::MAP);
    for (std::size_t index = 0; index != object_.via.map.size; index++) {
      action(UnPacker(object_.via.map.ptr[index].key),
             UnPacker(object_.via.map.ptr[index].val));
    }
  }

private:
  const ::msgpack::object object_;
};

} // namespace core
} // namespace kr

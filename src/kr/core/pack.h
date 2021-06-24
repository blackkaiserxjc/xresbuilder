#pragma once

#include <string_view>

#include <kr/core/type.h>

namespace kr {
namespace core {
template <typename Stream>
struct Packer
{
    Packer &pack(bool value);
    Packer &pack(std::int32_t value);
    Packer &pack(std::uint32_t value);
    Packer &pack(std::int64_t value);
    Packer &pack(std::uint64_t value);
    Packer &pack(double value);
    Packer &pack(std::string_view value);

    template <typename T>
    Packer &key(T value);
    template <typename T>
    Packer &kv(std::string_view key, T value);

    Packer &pack_begin_array(std::string_view name, std::size_t size);
    Packer &pack_begin_array(std::size_t size);
    Packer &pack_end_array();

    Packer &pack_begin_map(std::string_view name, std::size_t size);
    Packer &pack_begin_map(std::size_t size);
    Packer &pack_end_map();
};

template <typename Layer>
struct UnPacker
{
    template <typename T>
    T as() const;

    template <typename T, typename Action, typename Except>
    void to(Action &&action, Except &&except) const;

    template <typename Init, typename Action>
    void visit_array(Init &&init, Action &&action) const;

    template <typename Init, typename Action>
    void visit_map(Init &&init, Action &&action) const;
};

} // namespace core
} // namespace kr

#include "detail/msgpack.h"

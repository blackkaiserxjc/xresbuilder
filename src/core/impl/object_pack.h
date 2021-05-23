#ifndef KR_APP_CORE_IMPL_OBJECT_PACK_H_
#define KR_APP_CORE_IMPL_OBJECT_PACK_H_

#include <exception>
#include <msgpack.hpp>

#include "type.h"

namespace kr {
namespace core {

template <>
void pack<Packer<msgpack::packer<msgpack::sbuffer>>, msgpack::object>(
    Packer<msgpack::packer<msgpack::sbuffer>> &packer, 
    const Type &type,
    msgpack::object &message) {
    Unpacker<msgpack::object> unpacker{message};
    if (IsPod(type.base_type)) {
        assert(type.base_type == unpacker.type(), "type not equal.");
        
        switch (type.base_type) {
        case BASE_TYPE_BOOL: {
            unpacker.template to<bool>(
                [&packer](bool value) { packer.pack(value); },
                [] { throw std::bad_cast("invaild_cast"); });
        } break;
        
        case BASE_TYPE_INT: {
            unpacker.template to<std::int64_t>(
                [&packer](std::int64_t value) { packer.pack(value); },
                []{ throw std::bad_cast("invalid_cast") });
        } break;
        
        case BASE_TYPE_FLOAT: {
            unpacker.template to<double>(
                [&packer](double value) { packer.pack(value); },
                []{ throw std::bad_cast("invaild_cast"); });
        } break;
        
        case BASE_TYPE_STRING: {
            unpacker.template to<std::string_view>(
                [&packer](std::string_view value) { packer.pack(value); },
                []{ throw std::bad_cast("invaild_cast");});
        } break;
        }
    } else if(IsObject(type.base_type)) {
        
    } else if(IsArray(type.base_type)) {
        assert(type.element == unpacker.type(), "type not equal.");
    }
}

} // namespace core
} // namespace kr
#endif
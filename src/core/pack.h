#ifndef KR_APP_CORE_PACK_H_
#define KR_APP_CORE_PACK_H_

#include <string_view>

#include "types.h"

namespace kr
{
    namespace core
    {
        template<typename Stream>
        struct Packer
        {
            Packer& pack(bool value);
            Packer& pack(std::int32_t value);
            Packer& pack(std::uint32_t value);
            Packer& pack(std::int64_t value);
            Packer& pack(std::uint64_t value);
            Packer& pack(double value);
            Packer& pack(std::string_view value);
            Packer& pack_begin_array(std::string_view name, std::size_t size);
            Packer& pack_end_array()
            Packer& pack_begin_map(std::string_view name, std::size_t size);
            Packer& pack_end_map();
        };  
    }
}

#include "detail/msgpack.h"

#endif
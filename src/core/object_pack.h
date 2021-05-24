#ifndef KR_APP_CORE_OBJECT_PACK_H_
#define KR_APP_CORE_OBJECT_PACK_H_

#include "type.h"
#include "pack.h"

namespace kr {
namespace core {

template <typename Packer, typename Reader>
void pack(Packer& packer, const Type& type, const Reader& reader);

template <typename Packer, typename Reader>
void pack_pod(Packer& packer, const Type& type, const Reader& message);

template <typename Packer, typename Reader>
void pack_object(Packer& packer, const Type& type, const Reader& message);

template <typename Packer, typename Reader>
void pack_array(Packer& packer, const Type& type, const Reader& message);

}
}

#include "impl/object_pack.h"

#endif
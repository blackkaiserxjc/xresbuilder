#ifndef KR_APP_CORE_OBJECT_PACK_H_
#define KR_APP_CORE_OBJECT_PACK_H_

#include "type.h"
#include "pack.h"

namespace kr {
namespace core {

template <typename Packer, typename Message>
void pack(Packer& packer, const Type& type, const Message& message);

}

}

#include "impl/object_pack.h"

#endif
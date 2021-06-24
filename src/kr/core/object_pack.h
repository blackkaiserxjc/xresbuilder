#pragma once

#include "pack.h"
#include "type.h"

namespace kr {
namespace core {

template <typename Packer, typename Reader>
class ObjectPacker
{
public:
    struct Context
    {
        Context()
            : row{}, field{};
        int row;
        std::string field;
    };

    ObjectPacker();
    ~ObjectPacker();

    void pack(Packer &packer, const Type &type, const Reader &reader);

protected:

    void pack_statement(Packer &packer, const Type &type, const Reader &reader);

    void pack_pod(Packer &packer, const Type &type, const Reader &reader);

    void pack_object(Packer &packer, const Type &type, const Reader &reader);

    void pack_array(Packer &packer, const Type &type, const Reader &reader);

    int depth_;
	Context ctx_;
};

template <typename Packer, typename Reader>
void pack(Packer &packer, const Type &type, const Reader &reader);

template <typename Packer, typename Reader>
void pack_statement(Packer &packer, const Type &type, const Reader &message);

template <typename Packer, typename Reader>
void pack_pod(Packer &packer, const Type &type, const Reader &message);

template <typename Packer, typename Reader>
void pack_object(Packer &packer, const Type &type, const Reader &message);

template <typename Packer, typename Reader>
void pack_array(Packer &packer, const Type &type, const Reader &message);

} // namespace core
} // namespace kr

#include "detail/object_pack.h"

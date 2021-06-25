#pragma once

#include <exception>

#include "pack.h"
#include "type.h"

namespace kr {
namespace core {

class BadCastException: public std::bad_cast 
{
public: 
    BadCastException(const std::string& what)
        : what_{what}
    {
    }

    virtual char const* what() const noexcept 
    {
        return !what_.empty() ? what_.c_str() : std::bad_cast::what();
    }

protected:
    std::string what_;
};

class ObjectPacker
{
public:
    struct Context
    {
        Context()
            : row{}, field{}
        {
        }
        int row;
        std::string field;
    };

    ObjectPacker()
        : depth_{}, ctx_{}
    {
    }
    ~ObjectPacker()
    {
    }

    template <typename Packer, typename Reader>
    void pack(Packer &packer, const Type &type, const Reader &reader);

    const Context &ctx() const
    {
        return ctx_;
    };

protected:
    template <typename Packer, typename Reader>
    void pack_pod(Packer &packer, const Type &type, const Reader &reader);

    template <typename Packer, typename Reader>
    void pack_object(Packer &packer, const Type &type, const Reader &reader);

    template <typename Packer, typename Reader>
    void pack_array(Packer &packer, const Type &type, const Reader &reader);

    int depth_;
    Context ctx_;
};
} // namespace core
} // namespace kr

#include "detail/object_pack.h"

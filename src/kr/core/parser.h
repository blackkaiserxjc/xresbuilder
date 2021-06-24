#pragma once

#include <string>

#include <kr/core/ast_builder.h>
#include <kr/core/object_pack.h>
#include <kr/core/pack.h>
#include <kr/core/type.h>

namespace kr {
namespace core {

class Parser
{
public:
    Parser() = default;
    ~Parser() = default;

    Parser(Parser &&) = default;
    Parser &operator=(Parser &&) = default;
    Parser(const Parser &) = delete;
    Parser &operator=(const Parser &) = delete;

    template <typename Packer>
    bool parse_object(const std::string &source, Packer &packer);

    bool parse_field(const std::string &source, Type &type);
};

} // namespace core
} // namespace kr

#include "detail/parser.h"
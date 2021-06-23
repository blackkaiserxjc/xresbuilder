#include "ast_builder.h"
#include "type.h"

namespace kr {
namespace core {

antlrcpp::Any IDLAstBuilder::visitPod(IDLParser::PodContext *ctx)
{
    BaseType base_type;
    if (ctx->Bool())
    {
        base_type = BASE_TYPE_BOOL;
    }
    else if (ctx->Int())
    {
        base_type = BASE_TYPE_INT;
    }
    else if (ctx->Long())
    {
        base_type = BASE_TYPE_LONG;
    }
    else if (ctx->Float())
    {
        base_type = BASE_TYPE_FLOAT;
    }
    else if (ctx->String())
    {
        base_type = BASE_TYPE_STRING;
    }
    return Type{base_type};
}

antlrcpp::Any IDLAstBuilder::visitObject(IDLParser::ObjectContext *ctx)
{
    auto fields = ctx->field();
    auto object = std::make_shared<ObjectDef>();
    for (std::size_t index = 0; index < fields.size(); index++)
    {
        auto field_def = visitField(fields[index]).as<std::shared_ptr<FieldDef>>();
        field_def->index = index;
        object->fields.add(field_def->name, field_def);
    }
    return Type{BASE_TYPE_OBJECT, object};
}

antlrcpp::Any IDLAstBuilder::visitField(IDLParser::FieldContext *ctx)
{
    auto field = std::make_shared<FieldDef>();
    if (ctx->Identifier() && ctx->statement())
    {
        field->name = ctx->Identifier()->getText();
        field->value.type = visitStatement(ctx->statement()).as<Type>();
    }
    return field;
}

antlrcpp::Any IDLAstBuilder::visitArray(IDLParser::ArrayContext *ctx)
{
    Type array{BASE_TYPE_ARRAY};
    if (ctx->statement())
    {
        auto element_type = visitStatement(ctx->statement()).as<Type>();
        array.element = element_type.base_type;
        array.obj_def = element_type.obj_def;
    }
    return array;
}

} // namespace core
} // namespace kr
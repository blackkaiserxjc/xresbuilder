#include "idl_visitor.h"
#include "idl.h"

namespace kr
{
    namespace core
    {

        antlrcpp::Any IDLParseVisitor::visitPod(IDLParser::PodContext *ctx)
        {
            Type pod;
            if (ctx->Bool())
            {
                pod.base_type = BASE_TYPE_BOOL;
            }
            else if (ctx->Int())
            {
                pod.base_type = BASE_TYPE_INT;
            }
            else if (ctx->Float())
            {
                pod.base_type = BASE_TYPE_FLOAT;
            }
            else if (ctx->String())
            {
                pod.base_type = BASE_TYPE_STRING;
            }
            return pod;
        }

        antlrcpp::Any IDLParseVisitor::visitObject(IDLParser::ObjectContext *ctx)
        {
            auto data = std::make_shared<ObjectDef>();
            Type type{BASE_TYPE_OBJECT, data};
            for (auto context : ctx->field())
            {
                auto field = visitField(context).as<FieldDef>();
                data->fields.Add(field.name, std::make_shared<FieldDef>(field));
            }
            return type;
        }

        antlrcpp::Any IDLParseVisitor::visitField(IDLParser::FieldContext *ctx)
        {
            FieldDef field;
            if (ctx->Identifier() && ctx->statement())
            {
                field.name = ctx->Identifier()->getText();
                field.value.type = visitStatement(ctx->statement()).as<Type>();
            }
            return field;
        }

        antlrcpp::Any IDLParseVisitor::visitArray(IDLParser::ArrayContext *ctx)
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
    }
}
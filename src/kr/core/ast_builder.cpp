#include <exception>

#include "ast_builder.h"
#include "type.h"

namespace kr {
namespace core {

ErrorStrategy::ErrorStrategy()
{
}

ErrorStrategy::~ErrorStrategy()
{
}

void ErrorStrategy::reportNoViableAlternative(antlr4::Parser *recognizer, const antlr4::NoViableAltException &e)
{
    antlr4::TokenStream *tokens = recognizer->getTokenStream();
    std::string input;
    if (tokens != nullptr)
    {
        if (e.getStartToken()->getType() == antlr4::Token::EOF)
        {
            input = "<EOF>";
        }
        else
        {
            input = tokens->getText(e.getStartToken(), e.getOffendingToken());
        }
    }
    else
    {
        input = "<unknown input>";
    }
    std::string msg = "no viable alternative at input " + escapeWSAndQuote(input);
    throw std::runtime_error(msg);
}

void ErrorStrategy::reportInputMismatch(antlr4::Parser *recognizer, const antlr4::InputMismatchException &e)
{
    std::string msg = "mismatched input " + getTokenErrorDisplay(e.getOffendingToken()) + " expecting " + e.getExpectedTokens().toString(recognizer->getVocabulary());
    throw std::runtime_error(msg);
}

void ErrorStrategy::reportFailedPredicate(antlr4::Parser *recognizer, const antlr4::FailedPredicateException &e)
{
    const std::string &ruleName = recognizer->getRuleNames()[recognizer->getContext()->getRuleIndex()];
    std::string msg = "rule " + ruleName + " " + e.what();
    throw std::runtime_error(msg);
}

void ErrorStrategy::reportMissingToken(antlr4::Parser *recognizer)
{
    if (inErrorRecoveryMode(recognizer))
    {
        return;
    }
    beginErrorCondition(recognizer);

    auto t = recognizer->getCurrentToken();
    antlr4::misc::IntervalSet expecting = getExpectedTokens(recognizer);
    std::string expectedText = expecting.toString(recognizer->getVocabulary());
    std::string msg = "missing " + expectedText + " at " + getTokenErrorDisplay(t);
    throw std::runtime_error(msg);
}

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
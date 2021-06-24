
// Generated from Cell.g4 by ANTLR 4.9.1

#pragma once

#include "CellVisitor.h"
#include "antlr4-runtime.h"

/**
 * This class provides an empty implementation of CellVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class CellBaseVisitor : public CellVisitor
{
public:
    virtual antlrcpp::Any visitProgram(CellParser::ProgramContext *ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitStatement(CellParser::StatementContext *ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitObject(CellParser::ObjectContext *ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitField(CellParser::FieldContext *ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitPod(CellParser::PodContext *ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitArray(CellParser::ArrayContext *ctx) override
    {
        return visitChildren(ctx);
    }
};


// Generated from Cell.g4 by ANTLR 4.9.1

#pragma once

#include "CellParser.h"
#include "antlr4-runtime.h"

/**
 * This interface defines an abstract listener for a parse tree produced by CellParser.
 */
class CellListener : public antlr4::tree::ParseTreeListener
{
public:
    virtual void enterProgram(CellParser::ProgramContext *ctx) = 0;
    virtual void exitProgram(CellParser::ProgramContext *ctx) = 0;

    virtual void enterStatement(CellParser::StatementContext *ctx) = 0;
    virtual void exitStatement(CellParser::StatementContext *ctx) = 0;

    virtual void enterObject(CellParser::ObjectContext *ctx) = 0;
    virtual void exitObject(CellParser::ObjectContext *ctx) = 0;

    virtual void enterField(CellParser::FieldContext *ctx) = 0;
    virtual void exitField(CellParser::FieldContext *ctx) = 0;

    virtual void enterPod(CellParser::PodContext *ctx) = 0;
    virtual void exitPod(CellParser::PodContext *ctx) = 0;

    virtual void enterArray(CellParser::ArrayContext *ctx) = 0;
    virtual void exitArray(CellParser::ArrayContext *ctx) = 0;
};

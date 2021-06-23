
// Generated from Cell.g4 by ANTLR 4.9.1

#pragma once

#include "CellListener.h"
#include "antlr4-runtime.h"

/**
 * This class provides an empty implementation of CellListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class CellBaseListener : public CellListener
{
public:
    virtual void enterProgram(CellParser::ProgramContext * /*ctx*/) override
    {
    }
    virtual void exitProgram(CellParser::ProgramContext * /*ctx*/) override
    {
    }

    virtual void enterStatement(CellParser::StatementContext * /*ctx*/) override
    {
    }
    virtual void exitStatement(CellParser::StatementContext * /*ctx*/) override
    {
    }

    virtual void enterObject(CellParser::ObjectContext * /*ctx*/) override
    {
    }
    virtual void exitObject(CellParser::ObjectContext * /*ctx*/) override
    {
    }

    virtual void enterField(CellParser::FieldContext * /*ctx*/) override
    {
    }
    virtual void exitField(CellParser::FieldContext * /*ctx*/) override
    {
    }

    virtual void enterPod(CellParser::PodContext * /*ctx*/) override
    {
    }
    virtual void exitPod(CellParser::PodContext * /*ctx*/) override
    {
    }

    virtual void enterArray(CellParser::ArrayContext * /*ctx*/) override
    {
    }
    virtual void exitArray(CellParser::ArrayContext * /*ctx*/) override
    {
    }

    virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override
    {
    }
    virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override
    {
    }
    virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override
    {
    }
    virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override
    {
    }
};

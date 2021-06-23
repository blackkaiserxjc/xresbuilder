
// Generated from IDL.g4 by ANTLR 4.9.1

#pragma once

#include "IDLParser.h"
#include "antlr4-runtime.h"

/**
 * This class defines an abstract visitor for a parse tree
 * produced by IDLParser.
 */
class IDLVisitor : public antlr4::tree::AbstractParseTreeVisitor
{
public:
    /**
   * Visit parse trees produced by IDLParser.
   */
    virtual antlrcpp::Any visitProgram(IDLParser::ProgramContext *context) = 0;

    virtual antlrcpp::Any visitStatement(IDLParser::StatementContext *context) = 0;

    virtual antlrcpp::Any visitPod(IDLParser::PodContext *context) = 0;

    virtual antlrcpp::Any visitObject(IDLParser::ObjectContext *context) = 0;

    virtual antlrcpp::Any visitField(IDLParser::FieldContext *context) = 0;

    virtual antlrcpp::Any visitArray(IDLParser::ArrayContext *context) = 0;
};

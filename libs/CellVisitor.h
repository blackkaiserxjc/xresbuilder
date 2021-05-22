
// Generated from Cell.g4 by ANTLR 4.9.1

#pragma once


#include "antlr4-runtime.h"
#include "CellParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by CellParser.
 */
class  CellVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by CellParser.
   */
    virtual antlrcpp::Any visitProgram(CellParser::ProgramContext *context) = 0;

    virtual antlrcpp::Any visitStatement(CellParser::StatementContext *context) = 0;

    virtual antlrcpp::Any visitObject(CellParser::ObjectContext *context) = 0;

    virtual antlrcpp::Any visitField(CellParser::FieldContext *context) = 0;

    virtual antlrcpp::Any visitPod(CellParser::PodContext *context) = 0;

    virtual antlrcpp::Any visitArray(CellParser::ArrayContext *context) = 0;


};


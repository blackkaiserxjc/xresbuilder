
// Generated from Field.g4 by ANTLR 4.9.1

#pragma once


#include "antlr4-runtime.h"
#include "FieldParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by FieldParser.
 */
class  FieldVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by FieldParser.
   */
    virtual antlrcpp::Any visitProg(FieldParser::ProgContext *context) = 0;

    virtual antlrcpp::Any visitStatement(FieldParser::StatementContext *context) = 0;

    virtual antlrcpp::Any visitPod(FieldParser::PodContext *context) = 0;

    virtual antlrcpp::Any visitObject(FieldParser::ObjectContext *context) = 0;

    virtual antlrcpp::Any visitField(FieldParser::FieldContext *context) = 0;

    virtual antlrcpp::Any visitArray(FieldParser::ArrayContext *context) = 0;


};


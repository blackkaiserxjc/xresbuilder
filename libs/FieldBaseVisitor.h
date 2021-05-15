
// Generated from Field.g4 by ANTLR 4.9.1

#pragma once


#include "antlr4-runtime.h"
#include "FieldVisitor.h"


/**
 * This class provides an empty implementation of FieldVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  FieldBaseVisitor : public FieldVisitor {
public:

  virtual antlrcpp::Any visitProg(FieldParser::ProgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStatement(FieldParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPod(FieldParser::PodContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitObject(FieldParser::ObjectContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitField(FieldParser::FieldContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitArray(FieldParser::ArrayContext *ctx) override {
    return visitChildren(ctx);
  }


};


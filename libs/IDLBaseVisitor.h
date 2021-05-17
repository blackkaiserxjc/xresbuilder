
// Generated from IDL.g4 by ANTLR 4.9.1

#pragma once


#include "antlr4-runtime.h"
#include "IDLVisitor.h"


/**
 * This class provides an empty implementation of IDLVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  IDLBaseVisitor : public IDLVisitor {
public:

  virtual antlrcpp::Any visitProg(IDLParser::ProgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStatement(IDLParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPod(IDLParser::PodContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitObject(IDLParser::ObjectContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitField(IDLParser::FieldContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitArray(IDLParser::ArrayContext *ctx) override {
    return visitChildren(ctx);
  }


};


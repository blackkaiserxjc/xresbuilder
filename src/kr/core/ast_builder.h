#pragma once

#include "CellBaseVisitor.h"
#include "IDLBaseVisitor.h"
#include "antlr4-runtime.h"
#include "pack.h"

namespace kr {
namespace core {

/** 数据单元访问者模式解析 */
template <typename Packer> class CellAstBuilder final : public CellBaseVisitor {
public:
  CellAstBuilder(Packer &packer);

  CellAstBuilder(const CellAstBuilder &) = delete;
  CellAstBuilder &operator=(const CellAstBuilder &) = delete;

  CellAstBuilder(CellAstBuilder &&) = default;
  CellAstBuilder &operator=(CellAstBuilder &&) = default;

  antlrcpp::Any visitObject(CellParser::ObjectContext *context) override;

  antlrcpp::Any visitField(CellParser::FieldContext *context) override;

  antlrcpp::Any visitPod(CellParser::PodContext *context) override;

  antlrcpp::Any visitArray(CellParser::ArrayContext *context) override;

private:
  Packer &packer_;
};

/** 字段访问器模式解析 */
class IDLAstBuilder final : public IDLBaseVisitor {
public:
  antlrcpp::Any visitPod(IDLParser::PodContext *context) override;

  antlrcpp::Any visitObject(IDLParser::ObjectContext *context) override;

  antlrcpp::Any visitField(IDLParser::FieldContext *context) override;

  antlrcpp::Any visitArray(IDLParser::ArrayContext *context) override;
};

} // namespace core
} // namespace kr


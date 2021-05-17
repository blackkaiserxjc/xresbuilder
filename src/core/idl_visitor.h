#ifndef KR_APP_CORE_IDL_VISITOR_H_
#define KR_APP_CORE_IDL_VISITOR_H

#include "antlr4-runtime.h"
#include "IDLBaseVisitor.h"

namespace kr
{
    namespace core
    {
        /** 遍历用的访问器 */
        class IDLParseVisitor final : public IDLBaseVisitor
        {
        public:
            antlrcpp::Any visitPod(IDLParser::PodContext *ctx) override;

            antlrcpp::Any visitObject(IDLParser::ObjectContext *ctx) override;

            antlrcpp::Any visitField(IDLParser::FieldContext *ctx) override;

            antlrcpp::Any visitArray(IDLParser::ArrayContext *ctx) override;
        };
    } // namespace core
} // namespace kr

#endif
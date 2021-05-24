#include <boost/algorithm/string.hpp>
#include <boost/convert.hpp>
#include <boost/convert/stream.hpp>

struct boost::cnv::by_default : public boost::cnv::cstream {};

namespace kr 
{
    namespace core
    {
        template <typename Packer>
        CellAstBuilder<Packer>::CellAstBuilder(Packer& packer)
            :packer_{packer}
        {}

        template <typename Packer>
        antlrcpp::Any CellAstBuilder<Packer>::visitObject(CellParser::ObjectContext *context)
        {   
            auto filed_size = context->field().size();
            packer_.pack_begin_map(filed_size);
            for (auto index = 0; index < filed_size; index++)
            {
                packer_.key(static_cast<std::uint32_t>(index + 1));
                visitField(context->field(index));
            }
            packer_.pack_end_map();
            return nullptr;
        }

        template <typename Packer>
        antlrcpp::Any CellAstBuilder<Packer>::visitField(CellParser::FieldContext *context)
        {
            return visitChildren(context);
        }

        template <typename Packer>
        antlrcpp::Any CellAstBuilder<Packer>::visitPod(CellParser::PodContext *context)
        {
            auto cvt = [](auto text)
            {
                boost::algorithm::trim_if(text, [](auto ch) { return ch == '\"';});
                boost::algorithm::to_lower(text);
                return text;
            };
            boost::cnv::cstream cnv;
            if (context->BooleanLiteral())
            {
                packer_.pack(boost::convert<bool>(cvt(context->BooleanLiteral()->getText()), cnv(std::boolalpha)).value_or(false));
            }
            else if (context->IntegerLiteral())
            {
                packer_.pack(boost::convert<std::int64_t>(cvt(context->IntegerLiteral()->getText())).value_or(0));
            }
            else if (context->FloatingLiteral())
            {
                packer_.pack(boost::convert<double>(cvt(context->FloatingLiteral()->getText())).value_or(0.0f));
            }
            else if (context->StringLiteral())
            {
                packer_.pack(cvt(context->StringLiteral()->getText()));
            } 
            return nullptr; 
        }
        
        template <typename Packer>
        antlrcpp::Any CellAstBuilder<Packer>::visitArray(CellParser::ArrayContext *context)
        {
            packer_.pack_begin_array(context->statement().size());
            for (auto ctx : context->statement())
            {
                visitStatement(ctx);
            }
            packer_.pack_end_array();
            return nullptr;
        }
    }   
}
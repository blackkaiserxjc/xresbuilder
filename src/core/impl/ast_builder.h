#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/convert.hpp>
#include <boost/convert/stream.hpp>

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
            using boost::convert;
            boost::cnv::cstream cnv;
            auto lower = [](auto node)
            {
                return boost::algorithm::to_lower_copy(node->getText());
            };
            if (context->BooleanLiteral())
            {
                auto value = convert<bool>(lower(context->BooleanLiteral()),cnv(std::boolalpha)).value_or(false);
                packer_.pack(value);
            }
            else if (context->IntegerLiteral())
            {
                packer_.pack(boost::lexical_cast<std::int64_t>(lower(context->IntegerLiteral())));
            }
            else if (context->FloatingLiteral())
            {
                packer_.pack(boost::lexical_cast<double>(lower(context->FloatingLiteral())));
            }
            else if (context->StringLiteral())
            {
                packer_.pack(lower(context->StringLiteral()));
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
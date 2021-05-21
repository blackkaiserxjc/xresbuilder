#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

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
            packer_.pack_map_begin(filed_size);
            for (auto index = 0; index < filed_size; index++)
            {
                packer_.key<std::uint32_t>(index + 1);
                visitField(context->field(index));
            }
            Packer::packer_.pack_map_end();
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
            auto lower = [](auto node)
            {
                return boost::algorithm::to_lower_copy(node->getText());
            };
            if (context->BooleanLiteral())
            {
                packer_.pack_bool(boost::lexical_cast<bool>(lower(context->BooleanLiteral())));
            }
            else if (context->IntegerLiteral())
            {
                packer_.pack_int64(boost::lexical_cast<std::int64_t>(lower(context->IntegerLiteral())));
            }
            else if (context->FloatingLiteral())
            {
                packer_.pack_double(boost::lexical_cast<double>(lower(context->FloatingLiteral())));
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
            packer_.pack_array_begin(context->statement().size());
            for (auto ctx : context->statement())
            {
                visitStatement(ctx);
            }
            packer_.pack_array_end();
            return nullptr;
        }
    }   
}
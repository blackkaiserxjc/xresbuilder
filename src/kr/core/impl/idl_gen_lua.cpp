#include <fmt/format.h>

#include <kr/core/code_generator.h>
#include <kr/core/idl.h>

namespace kr {
namespace core {
namespace lua {

std::string generated_filename(const std::string &path, const std::string &file_name)
{
    return fmt::format("{}{}.json", path, file_name);
}

}

class LuaGenerator : public CodeGenerator {
public:
    LuaGenerator(Model& model, const std::string& path, const std::string& file_name)
        :CodeGenerator(model, path, file_name)
    {}

    bool generate()
    {
        return true;
    }
};

}
}
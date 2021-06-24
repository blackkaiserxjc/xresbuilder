#pragma once
#include <functional>
#include <string>

#include <kr/core/idl.h>

namespace kr {
namespace core {

class Model;
class Compiler
{
public:
    struct Generator
    {
        using GeneratedFn =
            std::function<bool(Model &model, const IDLOptions &,
                const std::string &, const std::string &)>;
        GeneratedFn generate;
        const char *generator_opt;
        const char *language;
        IDLOptions::Language lang;
        const char *generator_help;
    };

    using DebugFn = std::function<void(const std::string &)>;
    using WarnFn = std::function<void(const std::string &)>;
    using ErrorFn = std::function<void(const std::string &)>;

    struct InitParams
    {
        InitParams()
            : generators(nullptr),
              num_generators(0),
              warn_fn{},
              error_fn{},
              debug_fn{} {};

        const Generator *generators;
        size_t num_generators;
        WarnFn warn_fn;
        ErrorFn error_fn;
        DebugFn debug_fn;
    };

    explicit Compiler(const InitParams &params)
        : params_(params)
    {
    }
    int run(int argc, char **argv);
    int run_with_gui(const IDLOptions &options);

private:
    void generate(const IDLOptions &options);
    void warn(const std::string &warn);
    void error(const std::string &error);
    void debug(const std::string &debug);

    InitParams params_;
};

} // namespace core
} // namespace kr
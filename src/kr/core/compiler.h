#pragma once

#include <functional>
#include <string>

#include <kr/core/idl.h>

namespace kr {
namespace core {

class Model;
class Compiler {
public:
  struct Options {
    enum Language { kLua = 1 << 0, kJson = 1 << 1, kMax };
    std::string src;
    std::string dest;
    std::uint32_t lang_to_generate;
  };

  struct Generator {
    using GeneratedFn = std::function<bool(Model &model, const std::string &,
                                           const std::string &)>;
    GeneratedFn generate;
    const char *generator_opt;
    const char *language;
    Options::Language lang;
    const char *generator_help;
  };

  struct InitParams {
    InitParams() : generators(nullptr), num_generators(0){};

    const Generator *generators;
    size_t num_generators;
  };

  explicit Compiler(const InitParams &params) : params_(params) {}
  int run(int argc, char **argv);

private:
  void generate(const Options &options);
  
  InitParams params_;
};

} // namespace core
} // namespace kr
#pragma once
#include <functional>
#include <string>

#include <kr/core/idl.h>

namespace kr {
namespace core {

class Model;
class Compiler {
public:

  struct Generator {
    using GeneratedFn = std::function<bool(Model &model, const IDLOptions&, const std::string &,
                                           const std::string &)>;
    GeneratedFn generate;
    const char *generator_opt;
    const char *language;
    IDLOptions::Language lang;
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
  void generate(const IDLOptions &options);
  
  InitParams params_;
};

} // namespace core
} // namespace kr
#ifndef CHIP8_COMPILER_H
#define CHIP8_COMPILER_H

#include <string>
#include <unordered_set>

#include "base/Aliases.h"
#include "base/Rom.h"
#include "configuration/MachineSpecification.h"

namespace chip8 {

/**
 * Complier translates ROM to binary format.
 * It supports only hexadecimal ROMs for now.
 */
class Compiler {
 public:
  Compiler(const MachineSpecification& spec, bool enable_checks);

  Compiler(const Compiler&) = delete;
  Compiler& operator=(const Compiler&) = delete;
  Compiler(Compiler&&) = delete;
  Compiler& operator=(Compiler&&) = delete;

  /**
   * Translates ROM to binary format.
   * @param text - ROM in hexadecimal format.
   * @throws SyntaxException when ROM contains syntax errors.
   * @throws SemanticException when ROM contains semantic errors.
   */
  Rom compile(std::string_view text);

 private:
  static std::unordered_set<word> allowed_f_opcodes_;
  bool enable_checks_;
  MachineSpecification spec_;

  struct Context {
    int line;
    int column;
  };

  void checkOpcode(word op, Context ctx);
  void check0(word op, Context ctx);
  void check5(word op, Context ctx);
  void check8(word op, Context ctx);
  void check9(word op, Context ctx);
  void checkE(word op, Context ctx);
  void checkF(word op, Context ctx);
};

} // namespace chip8

#endif // CHIP8_COMPILER_H

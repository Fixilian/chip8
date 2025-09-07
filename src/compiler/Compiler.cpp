#include "Compiler.h"

#include <memory>

#include "base/BitOperations.h"
#include "exception/OutOfRangeException.h"
#include "exception/SemanticException.h"
#include "HexRomParser.h"
#include "Parser.h"
#include "RomBuilder.h"

using namespace std;

namespace chip8 {


unordered_set<word> Compiler::allowed_f_opcodes_ = {
  0x07, 0x0A, 0x15, 0x18, 0x1E, 0x29, 0x33, 0x55, 0x65
};


Compiler::Compiler(const MachineSpecification& spec, bool enable_checks)
    : enable_checks_(enable_checks),
      spec_(spec)
{}


Rom Compiler::compile(string_view text) {
  unique_ptr<Parser> parser = make_unique<HexRomParser>(text);
  RomBuilder builder(spec_.getMemorySize());

  try {
    word w;

    while ((w = parser->next())) {
      if (enable_checks_) {
        checkOpcode(w, {parser->getLine(), parser->getColumn()});
      }
      builder.push(w);
    }

  } catch(const OutOfRangeException& ex) {
    throw SemanticException("ROM is too big for current configuration");
  }

  return builder.build();
}


void Compiler::checkOpcode(word op, Context ctx) {
  word first_digit = highest4BitsOf(op);
  switch (first_digit) {
  case 0x0: check0(op, ctx); break;
  case 0x5: check5(op, ctx); break;
  case 0x8: check8(op, ctx); break;
  case 0x9: check9(op, ctx); break;
  case 0xE: checkE(op, ctx); break;
  case 0xF: checkF(op, ctx); break;
  default: break;
  }
}


void Compiler::check0(word op, Context ctx) {
  word addr = lowest12BitsOf(op);
  if (addr < spec_.getReservedMemorySize()) {
    if (addr != 0xE0 && addr != 0xEE) {
      throw SemanticException(ctx.line, ctx.column, "Unknown opcode");
    }
  }
}


void Compiler::check5(word op, Context ctx) {
  word last_digit = lowest4BitsOf(op);
  if (last_digit != 0x0) {
    throw SemanticException(ctx.line, ctx.column, "Unknown opcode");
  }
}


void Compiler::check8(word op, Context ctx) {
  word last_digit = lowest4BitsOf(op);
  if (!(last_digit <= 0x7 || last_digit == 0xE)) {
    throw SemanticException(ctx.line, ctx.column, "Unknown opcode");
  }
}


void Compiler::check9(word op, Context ctx) {
  word last_digit = lowest4BitsOf(op);
  if (last_digit != 0x0) {
    throw SemanticException(ctx.line, ctx.column, "Unknown opcode");
  }
}


void Compiler::checkE(word op, Context ctx) {
  word kk = lowest8BitsOf(op);
  if (kk != 0x9E && kk != 0xA1) {
    throw SemanticException(ctx.line, ctx.column, "Unknown opcode");
  }
}


void Compiler::checkF(word op, Context ctx) {
  word kk = lowest8BitsOf(op);
  if (!allowed_f_opcodes_.contains(kk)) {
    throw SemanticException(ctx.line, ctx.column, "Unknown opcode");
  }
}


} // namespace chip8

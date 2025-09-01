#include "RandomInstruction.h"

#include <cstdlib>
#include <ctime>

#include "base/BitOperations.h"

using namespace std;

namespace chip8 {


RandomInstruction::RandomInstruction(word opcode) 
    : Instruction(opcode)
{}  


void RandomInstruction::execute(ExecutionContext& ctx) {
  word x = getXFrom(opcode_);
  word kk = lowest8BitsOf(opcode_);
  srand(static_cast<unsigned int>(time({})));
  int r = rand() % kByteMax;
  ctx.registers[x] = static_cast<byte>(r & kk);
}


} // namespace chip8

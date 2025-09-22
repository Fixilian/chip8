#include "Cpu.h"

#include <chrono>

#include "base/Log.h"
#include "base/Timer.h"
#include "execution/Chip8Decoder.h"
#include "execution/EndOfProgramDetector.h"
#include "instruction/Instruction.h"
#include "instruction/InstructionPtr.h"

using namespace std;

namespace chip8 {

constexpr int kInstructionsCount = 16;


Cpu::Cpu(Memory& memory, ExecutionContext& ctx, Endianness endian)
    : memory_(memory),
      ctx_(ctx),
      allocator_(sizeof(Instruction), kInstructionsCount),
      decoder_(make_unique<Chip8Decoder>(allocator_)),
      running_(false),
      endian_(endian)
{}


void Cpu::execute(Rom rom) {
  memory_.load(rom);
  ctx_.pc = memory_.getRomBegin();

  EndOfProgramDetector detector(memory_, ctx_);

  Timer timer;
  chrono::milliseconds interval(16); // 60 Hz
  timer.start(interval, [&] () { ctx_.updateTimers(); });

  running_ = true;
  Log::trace(memory_.toString());
  while (running_) {
    auto pc = reinterpret_cast<const word*>(ctx_.pc);
    word opcode = *pc;
    opcode = byteSwapTo(endian_, opcode);
    if (detector.endOfProgram(opcode)) {
      break;
    }
    InstructionPtr ins = decoder_->decode(opcode);
    Log::trace(ins->toString());
    ins->execute(ctx_);
    Log::trace(ctx_.toString());
    ctx_.pc += kPcStep;
  }
  
  timer.stop();
}


void Cpu::stop() {
  running_ = false;
}


} // namespace chip8

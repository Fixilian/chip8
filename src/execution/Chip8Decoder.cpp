#include "Chip8Decoder.h"

#include "base/BitOperations.h"
#include "instruction/Instructions.h"

namespace chip8 {

using NopInstruction = SysJumpInstruction;


Chip8Decoder::Chip8Decoder(Allocator& allocator) 
    : allocator_(allocator)
{}


InstructionPtr Chip8Decoder::decode(word opcode) {
  word first_digit = highest4BitsOf(opcode);
  switch (first_digit) {
    case 0x0: return decode0nnn(opcode);
    case 0x1: return create<JumpInstruction>(opcode);
    case 0x2: return create<CallInstruction>(opcode);
    case 0x3: return create<SkipIfEqValueInstruction>(opcode);
    case 0x4: return create<SkipIfNeValueInstruction>(opcode);
    case 0x5: return decode5nnn(opcode);
    case 0x6: return create<LoadValueInstruction>(opcode);
    case 0x7: return create<AddValueInstruction>(opcode);
    case 0x8: return decode8nnn(opcode);
    case 0x9: return decode9nnn(opcode);
    case 0xA: return create<LoadIRegisterInstruction>(opcode);
    case 0xB: return create<JumpWithOffsetInstruction>(opcode);
    case 0xC: return create<RandomInstruction>(opcode);
    case 0xD: return create<DrawInstruction>(opcode);
    case 0xE: return decodeEnnn(opcode);
    case 0xF: return decodeFnnn(opcode);
    default: return create<NopInstruction>(opcode);
  }
}


InstructionPtr Chip8Decoder::decode0nnn(word op) {
  word nnn = lowest12BitsOf(op);
  switch (nnn) {
    case 0x0E0: return create<ClearDisplayInstruction>(op);
    case 0x0EE: return create<ReturnInstruction>(op);
    default: return create<SysJumpInstruction>(op);
  }
}


InstructionPtr Chip8Decoder::decode5nnn(word op) {
  word last_digit = lowest4BitsOf(op);
  if (last_digit == 0x0) {
    return create<SkipIfEqRegisterInstruction>(op);
  } else {
    return create<NopInstruction>(op);
  }
}


InstructionPtr Chip8Decoder::decode8nnn(word op) {
  word last_digit = lowest4BitsOf(op);
  switch (last_digit) {
    case 0x0: return create<LoadRegisterInstruction>(op);
    case 0x1: return create<BitwiseOrInstruction>(op);
    case 0x2: return create<BitwiseAndInstruction>(op);
    case 0x3: return create<BitwiseXorInstruction>(op);
    case 0x4: return create<AddRegisterInstruction>(op);
    case 0x5: return create<SubRegisterInstruction>(op);
    case 0x6: return create<ShiftRightInstruction>(op);
    case 0x7: return create<SubnInstruction>(op);
    case 0xE: return create<ShiftLeftInstruction>(op);
    default: return create<NopInstruction>(op);
  }
}


InstructionPtr Chip8Decoder::decode9nnn(word op) {
  word last_digit = lowest4BitsOf(op);
  if (last_digit == 0x0) {
    return create<SkipIfNeRegisterInstruction>(op);
  } else {
    return create<NopInstruction>(op);
  }
}


InstructionPtr Chip8Decoder::decodeEnnn(word op) {
  word last_2digits = lowest8BitsOf(op);
  switch (last_2digits) {
    case 0x9E: return create<SkipIfPressedInstruction>(op);
    case 0xA1: return create<SkipIfNotPressedInstruction>(op);
    default: return create<NopInstruction>(op);
  }
}


InstructionPtr Chip8Decoder::decodeFnnn(word op) {
  word last_2digits = lowest8BitsOf(op);
  switch (last_2digits) {
    case 0x07: return create<LoadDtInstruction>(op);
    case 0x0A: return create<WaitKeyPressInstruction>(op);
    case 0x15: return create<SetDelayTimerInstruction>(op);
    case 0x18: return create<SetSoundTimerInstruction>(op);
    case 0x1E: return create<AddIInstruction>(op);
    case 0x29: return create<GetSpriteLocationInstruction>(op);
    case 0x33: return create<StoreBcdInstruction>(op);
    case 0x55: return create<StoreInstruction>(op);
    case 0x65: return create<LoadInstruction>(op);
    default: return create<NopInstruction>(op);
  }
}


} // namespace chip8

#ifndef CHIP8_EXECUTION_CPU_H
#define CHIP8_EXECUTION_CPU_H

#include <atomic>
#include <memory>

#include "base/Allocator.h"
#include "base/Endian.h"
#include "base/Rom.h"
#include "execution/Decoder.h"
#include "instruction/ExecutionContext.h"
#include "memory/Memory.h"

namespace chip8 {

/**
 * Central processing unit.
 */
class Cpu {
 public:
  Cpu(Memory& memory, ExecutionContext& ctx, Endianness endian);

  void execute(Rom rom);

  void stop();

 private:
  Memory& memory_;
  ExecutionContext& ctx_;
  Allocator allocator_;
  std::unique_ptr<Decoder> decoder_;
  std::atomic<bool> running_;
  Endianness endian_;
};

} // namespace chip8

#endif // CHIP8_EXECUTION_CPU_H

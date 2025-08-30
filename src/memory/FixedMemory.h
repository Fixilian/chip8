#ifndef CHIP8_MEMORY_FIXEDMEMORY_H
#define CHIP8_MEMORY_FIXEDMEMORY_H

#include <vector>

#include "Memory.h"

namespace chip8 {

/**
 * Random access memory.
 */
class FixedMemory : public Memory {
 public:
  FixedMemory(int size, int reserve);

  virtual ~FixedMemory();

  virtual void load(const Rom& rom) override;

  virtual const word* getRomBegin() override;
  virtual const word* getRomEnd() override;

  virtual byte& operator[](int index) override;
  virtual const byte& operator[](int index) const override;

  virtual const byte* getDigitSprite(int digit) override;

  virtual const byte* mem() const override;

 private:
  int size_;
  int reserve_;
  int user_mem_begin_;
  byte* mem_;
  word* rom_begin_;
  word* rom_end_;
  byte* sprites_;

  void setSprite(byte* p, byte b1, byte b2, byte b3, byte b4, byte b5);
};

} // namespace chip8

#endif // CHIP8_MEMORY_FIXEDMEMORY_H

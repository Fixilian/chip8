#include <gtest/gtest.h>

#include <vector>

#include "memory/FixedMemory.h"

using namespace std;
using namespace chip8;


TEST(RamTest, Load) {
  // Arrange
  constexpr int kRomSize = 6;
  word rom_source[kRomSize] = { 0x0000, 0xAABB, 0x0011, 0xCCDD, 0x0033, 0xEE55 };
  Rom rom(rom_source, kRomSize * sizeof(word));
  int reserve = 512;
  int size = 1024;
  FixedMemory ram(size, reserve);

  // Act
  ram.load(rom);

  // Assert
  auto actual_rom_size = ram.getRomEnd() - ram.getRomBegin();
  EXPECT_EQ(actual_rom_size, kRomSize);
  auto actual = ram.getRomBegin();
  for (int i = 0; i < kRomSize; i += 1) {
    EXPECT_EQ(actual[i], rom_source[i]);
  }
}


TEST(RamTest, RandomAccess) {
  // Arrange
  constexpr int kRomSize = 6;
  word rom_source[kRomSize] = { 0x0000, 0xAABB, 0x0011, 0xCCDD, 0x0033, 0xEE55 };
  vector<chip8::byte> expected = { 0x00, 0xAA, 0x11, 0xDD, 0x33, 0x55};
  int expected_len = static_cast<int>(expected.size());
  Rom rom(rom_source, kRomSize * sizeof(word));
  int reserve = 512;
  int size = 1024;
  FixedMemory ram(size, reserve);
  ram.load(rom);
  int start = reserve + kRomSize * sizeof(word);

  // Act
  for (int i = 0; i < expected_len; i += 1) {
    ram[start + i] = expected[i];
  }

  // Assert
  for (int i = 0; i < expected_len; i += 1) {
    EXPECT_EQ(ram[start + i], expected[i]);
  }
  const FixedMemory& r = ram;
  for (int i = 0; i < expected_len; i += 1) {
    EXPECT_EQ(r[start + i], expected[i]);
  }
}


TEST(RamTest, Sprites) {
  // Arrange
  int reserve = 512;
  int size = 1024;
  FixedMemory ram(size, reserve);
  vector<chip8::byte> sprite1 = { 0x20, 0x60, 0x20, 0x20, 0x70 };

  // Act
  auto sprite = ram.getDigitSprite(1);

  // Assert
  for (int i = 0; i < kDigitSpriteSize; i += 1) {
    EXPECT_EQ(sprite[i], sprite1[i]);
  }
}

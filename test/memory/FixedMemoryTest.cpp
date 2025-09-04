#include <gtest/gtest.h>

#include <vector>

#include "memory/FixedMemory.h"
#include "TestObjectFactory.h"

using namespace std;
using namespace chip8;


TEST(RamTest, Load) {
  // Arrange
  constexpr int kRomSize = 6;
  word rom_source[kRomSize] = { 0x0000, 0xAABB, 0x0011, 0xCCDD, 0x0033, 0xEE55 };
  Rom rom(rom_source, kRomSize * sizeof(word));
  auto mem = createMemory();

  // Act
  mem->load(rom);

  // Assert
  auto actual_rom_size = (mem->getRomEnd() - mem->getRomBegin()) / sizeof(word);
  EXPECT_EQ(actual_rom_size, kRomSize);
  auto actual = reinterpret_cast<const word*>(mem->getRomBegin());
  for (int i = 0; i < kRomSize; i += 1) {
    EXPECT_EQ(actual[i], rom_source[i]);
  }
}


TEST(RamTest, RandomAccess) {
  // Arrange
  constexpr int kRomSize = 6;
  word rom_source[kRomSize] = { 0x0000, 0xAABB, 0x0011, 0xCCDD, 0x0033, 0xEE55 };
  vector<chip8::byte> expected = { 0x00, 0xAA, 0x11, 0xDD, 0x33, 0x55};
  int n = static_cast<int>(expected.size());
  auto mem = createMemoryWithRom(rom_source, kRomSize);
  int start = static_cast<int>(mem->getRomEnd() - mem->mem());
  const Memory& cram = *mem;
  Memory& ram = *mem;

  // Act
  for (int i = 0; i < n; i += 1) {
    ram[start + i] = expected[i];
  }

  // Assert
  for (int i = 0; i < n; i += 1) {
    EXPECT_EQ(ram[start + i], expected[i]);
  }
  for (int i = 0; i < n; i += 1) {
    EXPECT_EQ(cram[start + i], expected[i]);
  }
}


TEST(RamTest, Sprites) {
  // Arrange
  auto mem = createMemory();
  vector<chip8::byte> sprite1 = { 0x20, 0x60, 0x20, 0x20, 0x70 };

  // Act
  auto sprite = mem->getDigitSprite(1);

  // Assert
  for (int i = 0; i < kDigitSpriteSize; i += 1) {
    EXPECT_EQ(sprite[i], sprite1[i]);
  }
}

#include <gtest/gtest.h>

#include <vector>

#include "execution/EndOfProgramDetector.h"
#include "instruction/ExecutionContext.h"
#include "memory/FixedMemory.h"
#include "TestObjectFactory.h"

using namespace std;
using namespace chip8;


TEST(EndOfProgramDetectorTest, EndOfRom) {
  // Arrange
  constexpr int kRomSize = 6;
  word rom_source[kRomSize] = { 0x0000, 0xAABB, 0x0011, 0xCCDD, 0x0033, 0xEE55 };
  vector<bool> expected = { false, false, false, false, false, false, true };
  vector<bool> actual(expected.size());

  auto keyboard = createKeyboardMonitor();
  auto mem = createMemoryWithRom(rom_source, kRomSize);
  auto ctx = createContext(*mem, *keyboard);
  EndOfProgramDetector detector(*mem, *ctx);

  // Act
  for (int i = 0; i < kRomSize; i += 1) {
    bool result = detector.endOfProgram(rom_source[i]);
    actual[i] = result;
    ctx->pc += kPcStep;
  } 
  actual[kRomSize] = detector.endOfProgram(0x0000);

  // Assert
  for (size_t i = 0; i < expected.size(); i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}


TEST(EndOfProgramDetectorTest, InfiniteLoop) {
  // Arrange
  constexpr int kRomSize = 6;
  word rom_source[kRomSize] = { 0x0000, 0xAABB, 0x0011, 0xCCDD, 0x0033, 0xEE55 };
  int loop_start_index = 3;
  vector<bool> expected = { false, false, false, true};
  vector<bool> actual(expected.size());

  auto keyboard = createKeyboardMonitor();
  auto mem = createMemoryWithRom(rom_source, kRomSize);
  auto ctx = createContext(*mem, *keyboard);
  EndOfProgramDetector detector(*mem, *ctx);

  word loop_addr = static_cast<word>(ctx->pc - mem->mem());
  word opcode = static_cast<word>(0x1000 + loop_addr + kPcStep * loop_start_index);
  rom_source[loop_start_index] = opcode;

  // Act
  for (int i = 0; i <= loop_start_index; i += 1) {
    bool result = detector.endOfProgram(rom_source[i]);
    actual[i] = result;
    ctx->pc += kPcStep;
  } 

  // Assert
  for (size_t i = 0; i < expected.size(); i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}



TEST(EndOfProgramDetectorTest, ReturnFromMain) {
  // Arrange
  constexpr int kRomSize = 6;
  word rom_source[kRomSize] = { 0x0000, 0xAABB, 0x0011, 0x00EE, 0x0033, 0xEE55 };
  vector<bool> expected = { false, false, false, true};
  vector<bool> actual(expected.size());
  int n = static_cast<int>(expected.size());

  auto keyboard = createKeyboardMonitor();
  auto mem = createMemoryWithRom(rom_source, kRomSize);
  auto ctx = createContext(*mem, *keyboard);
  EndOfProgramDetector detector(*mem, *ctx);

  // Act
  for (int i = 0; i <= n; i += 1) {
    bool result = detector.endOfProgram(rom_source[i]);
    actual[i] = result;
    ctx->pc += kPcStep;
  } 

  // Assert
  for (int i = 0; i < n; i += 1) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}

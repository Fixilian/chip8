#include <gtest/gtest.h>

#include <vector>

#include "execution/Cpu.h"
#include "TestObjectFactory.h"

using namespace std;
using namespace chip8;


TEST(CpuTest, Execute) {
  // Arrange
  constexpr int rom_size = 17;
  chip8::byte a = 10;
  chip8::byte b = 5;
  word rom_source[rom_size] = { 
    0x600A, // LD V0, 0x0A  ; Load decimal 10 into V0
    0x6105, // LD V1, 0x05  ; Load decimal 5 into V1

    0x8014, // ADD V0, V1   ; V0 = V0 + V1
    0x8200, // LD V2, V0    ; Copy V0 to V2

    0x8015, // SUB V0, V1   ; V0 = V0 - V1
    0x8300, // LD V3, V0    ; Copy V0 to V3

    0x801E, // SHL V0       ; V0 = V0 << 1
    0x8400, // LD V4, V0    ; Copy V0 to V4

    0x8016, // SHR V0       ; V0 = V0 >> 1
    0x8500, // LD V5, V0    ; Copy V0 to V5

    0x8011, // OR V0, V1    ; V0 = V0 | V1
    0x8600, // LD V6, V0    ; Copy V0 to V6

    0x8012, // AND V0, V1   ; V0 = V0 & V1
    0x8700, // LD V7, V0    ; Copy V0 to V7

    0x8013, // XOR V0, V1   ; V0 = V0 ^ V1
    0x8800, // LD V8, V0    ; Copy V0 to V8
    
    0x1220  // JP 220       ; infinite loop
  };
  Rom rom(rom_source, rom_size * sizeof(word));
  vector<chip8::byte> expected = { 
    static_cast<chip8::byte>(a += b), 
    static_cast<chip8::byte>(a -= b), 
    static_cast<chip8::byte>(a <<= 1), 
    static_cast<chip8::byte>(a >>= 1), 
    static_cast<chip8::byte>(a |= b),
    static_cast<chip8::byte>(a &= b),
    static_cast<chip8::byte>(a ^= b)
  };

  auto keyboard = createKeyboardMonitor();
  auto mem = createMemory();
  auto ctx = createContext(*mem, *keyboard);
  Cpu cpu(*mem, *ctx);

  // Act
  cpu.execute(rom);

  // Assert
  size_t registers_offset = 2;
  for (size_t i = 0; i < expected.size(); i += 1) {
    EXPECT_EQ(ctx->registers[registers_offset + i], expected[i]);
  }
}

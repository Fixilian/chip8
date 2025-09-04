#include <gtest/gtest.h>

#include <vector>

#include "base/Allocator.h"
#include "execution/Chip8Decoder.h"
#include "instruction/Instructions.h"

using namespace std;
using namespace chip8;


template <typename T, typename Base>
bool instanceof(Base* ptr) {
  if (T* v = dynamic_cast<T*>(ptr)) {
    return true;
  }
  return false;
}


TEST(Chip8DecoderTest, Decode) {
  // Arrange
  int block_size = sizeof(Instruction);
  int block_count = 128;
  Allocator allocator(block_size, block_count);
  Chip8Decoder d(allocator);

  // Act

  // Assert
  EXPECT_TRUE(instanceof<SysJumpInstruction>(d.decode(0x0FFF).get()));
  EXPECT_TRUE(instanceof<ClearDisplayInstruction>(d.decode(0x00E0).get()));
  EXPECT_TRUE(instanceof<ReturnInstruction>(d.decode(0x00EE).get()));

  EXPECT_TRUE(instanceof<JumpInstruction>(d.decode(0x1FFF).get()));
  EXPECT_TRUE(instanceof<CallInstruction>(d.decode(0x2FFF).get()));
  EXPECT_TRUE(instanceof<SkipIfEqValueInstruction>(d.decode(0x3FFF).get()));
  EXPECT_TRUE(instanceof<SkipIfNeValueInstruction>(d.decode(0x4FFF).get()));
  EXPECT_TRUE(instanceof<SkipIfEqRegisterInstruction>(d.decode(0x5FF0).get()));

  EXPECT_TRUE(instanceof<LoadValueInstruction>(d.decode(0x6FFF).get()));
  EXPECT_TRUE(instanceof<AddValueInstruction>(d.decode(0x7FFF).get()));

  EXPECT_TRUE(instanceof<LoadRegisterInstruction>(d.decode(0x8FF0).get()));
  EXPECT_TRUE(instanceof<BitwiseOrInstruction>(d.decode(0x8FF1).get()));
  EXPECT_TRUE(instanceof<BitwiseAndInstruction>(d.decode(0x8FF2).get()));
  EXPECT_TRUE(instanceof<BitwiseXorInstruction>(d.decode(0x8FF3).get()));
  EXPECT_TRUE(instanceof<AddRegisterInstruction>(d.decode(0x8FF4).get()));
  EXPECT_TRUE(instanceof<SubRegisterInstruction>(d.decode(0x8FF5).get()));
  EXPECT_TRUE(instanceof<ShiftRightInstruction>(d.decode(0x8FF6).get()));
  EXPECT_TRUE(instanceof<SubnInstruction>(d.decode(0x8FF7).get()));
  EXPECT_TRUE(instanceof<ShiftLeftInstruction>(d.decode(0x8FFE).get()));

  EXPECT_TRUE(instanceof<SkipIfNeRegisterInstruction>(d.decode(0x9FF0).get()));
  EXPECT_TRUE(instanceof<LoadIRegisterInstruction>(d.decode(0xAFFF).get()));
  EXPECT_TRUE(instanceof<JumpWithOffsetInstruction>(d.decode(0xBFFF).get()));
  EXPECT_TRUE(instanceof<RandomInstruction>(d.decode(0xCFFF).get()));
  EXPECT_TRUE(instanceof<DrawInstruction>(d.decode(0xDFFF).get()));

  EXPECT_TRUE(instanceof<SkipIfPressedInstruction>(d.decode(0xEF9E).get()));
  EXPECT_TRUE(instanceof<SkipIfNotPressedInstruction>(d.decode(0xEFA1).get()));

  EXPECT_TRUE(instanceof<LoadDtInstruction>(d.decode(0xFF07).get()));
  EXPECT_TRUE(instanceof<WaitKeyPressInstruction>(d.decode(0xFF0A).get()));
  EXPECT_TRUE(instanceof<SetDelayTimerInstruction>(d.decode(0xFF15).get()));
  EXPECT_TRUE(instanceof<SetSoundTimerInstruction>(d.decode(0xFF18).get()));
  EXPECT_TRUE(instanceof<AddIInstruction>(d.decode(0xFF1E).get()));
  EXPECT_TRUE(instanceof<GetSpriteLocationInstruction>(d.decode(0xFF29).get()));
  EXPECT_TRUE(instanceof<StoreBcdInstruction>(d.decode(0xFF33).get()));
  EXPECT_TRUE(instanceof<StoreInstruction>(d.decode(0xFF55).get()));
  EXPECT_TRUE(instanceof<LoadInstruction>(d.decode(0xFF65).get()));
}

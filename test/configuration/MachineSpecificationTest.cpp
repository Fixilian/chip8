#include <gtest/gtest.h>

#include <string>
#include <unordered_map>

#include "configuration/MachineSpecification.h"
#include "exception/InvalidArgumentException.h"
#include "exception/InvalidConfigException.h"

using namespace std;
using namespace chip8;


TEST(MachineSpecificationTest, SetConstants) {
  // Arrange
  MachineSpecification spec;
  int memory_size = 8192;
  int reserved_memory_size = 1024;
  int stack_size = 32;
  int display_width = 128;
  int display_height = 64;
  int timer_frequency = 144;

  // Act
  spec.setMemorySize(memory_size);
  spec.setReservedMemorySize(reserved_memory_size);
  spec.setStackSize(stack_size);
  spec.setDisplayWidth(display_width);
  spec.setDisplayHeight(display_height);
  spec.setTimerFrequency(timer_frequency);

  // Assert
  EXPECT_EQ(spec.getMemorySize(), memory_size);
  EXPECT_EQ(spec.getReservedMemorySize(), reserved_memory_size);
  EXPECT_EQ(spec.getStackSize(), stack_size);
  EXPECT_EQ(spec.getDisplayWidth(), display_width);
  EXPECT_EQ(spec.getDisplayHeight(), display_height);
  EXPECT_EQ(spec.getTimerFrequency(), timer_frequency);
}


TEST(MachineSpecificationTest, InvalidConstants) {
  // Arrange
  MachineSpecification spec;
  int memory_size = 1024;
  int reserved_memory_size = 128;
  int stack_size = 8;
  int display_width = 32;
  int display_height = 16;
  int timer_frequency1 = 30;
  int timer_frequency2 = 1000;

  // Act

  // Assert
  EXPECT_THROW({
    spec.setMemorySize(memory_size);
  }, InvalidArgumentException);

  EXPECT_THROW({
    spec.setReservedMemorySize(reserved_memory_size);
  }, InvalidArgumentException);

  EXPECT_THROW({
    spec.setStackSize(stack_size);
  }, InvalidArgumentException);

  EXPECT_THROW({
    spec.setDisplayWidth(display_width);
  }, InvalidArgumentException);

  EXPECT_THROW({
    spec.setDisplayHeight(display_height);
  }, InvalidArgumentException);

  EXPECT_THROW({
    spec.setTimerFrequency(timer_frequency1);
  }, InvalidArgumentException);

  EXPECT_THROW({
    spec.setTimerFrequency(timer_frequency2);
  }, InvalidArgumentException);
}

#include <gtest/gtest.h>

#include <string>
#include <unordered_map>

#include "configuration/Configuration.h"
#include "exception/InvalidArgumentException.h"
#include "exception/InvalidConfigException.h"

using namespace std;
using namespace chip8;


TEST(ConfigurationTest, SetConstants) {
  // Arrange
  Configuration cfg;
  int memory_size = 8192;
  int reserved_memory_size = 1024;
  int stack_size = 32;
  int display_width = 128;
  int display_height = 64;
  int timer_frequency = 144;

  // Act
  cfg.setMemorySize(memory_size);
  cfg.setReservedMemorySize(reserved_memory_size);
  cfg.setStackSize(stack_size);
  cfg.setDisplayWidth(display_width);
  cfg.setDisplayHeight(display_height);
  cfg.setTimerFrequency(timer_frequency);

  // Assert
  EXPECT_EQ(cfg.getMemorySize(), memory_size);
  EXPECT_EQ(cfg.getReservedMemorySize(), reserved_memory_size);
  EXPECT_EQ(cfg.getStackSize(), stack_size);
  EXPECT_EQ(cfg.getDisplayWidth(), display_width);
  EXPECT_EQ(cfg.getDisplayHeight(), display_height);
  EXPECT_EQ(cfg.getTimerFrequency(), timer_frequency);
}


TEST(ConfigurationTest, Keybinds) {
  // Arrange
  Configuration cfg;
  unordered_map<chip8::byte, chip8::byte> binds;
  binds['a'] = 0x1;
  binds['b'] = 0x2;
  binds['c'] = 0x3;
  binds['d'] = 0xC;
  binds['e'] = 0x4;
  binds['f'] = 0x5;
  binds['g'] = 0x6;
  binds['h'] = 0xD;
  binds['i'] = 0x7;
  binds['j'] = 0x8;
  binds['k'] = 0x9;
  binds['l'] = 0xE;
  binds['m'] = 0xA;
  binds['n'] = 0x0;
  binds['o'] = 0xB;
  binds['p'] = 0xF;

  // Act
  for (const auto&[key, to] : binds) {
    cfg.bindKey(key, to);
  } 

  // Assert
  auto keybinds = cfg.getKeybinds();
  for (const auto&[key, to] : binds) {
    EXPECT_TRUE(keybinds.contains(key));
    EXPECT_EQ(keybinds[key], to);
  } 
}


TEST(ConfigurationTest, InvalidConstants) {
  // Arrange
  Configuration cfg;
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
    cfg.setMemorySize(memory_size);
  }, InvalidArgumentException);

  EXPECT_THROW({
    cfg.setReservedMemorySize(reserved_memory_size);
  }, InvalidArgumentException);

  EXPECT_THROW({
    cfg.setStackSize(stack_size);
  }, InvalidArgumentException);

  EXPECT_THROW({
    cfg.setDisplayWidth(display_width);
  }, InvalidArgumentException);

  EXPECT_THROW({
    cfg.setDisplayHeight(display_height);
  }, InvalidArgumentException);

  EXPECT_THROW({
    cfg.setTimerFrequency(timer_frequency1);
  }, InvalidArgumentException);

  EXPECT_THROW({
    cfg.setTimerFrequency(timer_frequency2);
  }, InvalidArgumentException);
}


TEST(ConfigurationTest, BadKeybinds) {
  // Arrange
  Configuration cfg;
  unordered_map<chip8::byte, chip8::byte> binds;
  binds['a'] = 0x1;
  binds['a'] = 0x3;
  binds['c'] = 0x3;

  // Act
  for (const auto&[key, to] : binds) {
    cfg.bindKey(key, to);
  } 

  // Assert
  EXPECT_THROW({
    auto keybinds = cfg.getKeybinds();
  }, InvalidConfigException);
}

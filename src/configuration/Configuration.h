#ifndef CHIP8_CONFIGURATION_CONFIGURATION_H
#define CHIP8_CONFIGURATION_CONFIGURATION_H

#include <unordered_map>

#include "base/Aliases.h"

namespace chip8 {

/**
 * Configuration.
 * Contains most of the machine parameters. 
 * Provides bindings for keys of 16-key keypad. 
 * Every set function throw InvalidArgumentException.
 */
class Configuration {
 public:
  Configuration();

  Configuration(const Configuration&) = default;
  Configuration& operator=(const Configuration&) = default;
  Configuration(Configuration&&) = default;
  Configuration& operator=(Configuration&&) = default;

  void setMemorySize(int size);
  int getMemorySize() const;

  void setReservedMemorySize(int size);
  int getReservedMemorySize() const;

  void setStackSize(int size);
  int getStackSize() const;

  void setDisplayWidth(int width);
  int getDisplayWidth() const;

  void setDisplayHeight(int height);
  int getDisplayHeight() const;

  void setTimerFrequency(int freq);
  int getTimerFrequency() const;

  /**
   * @throws UnknownKeyException when 'to' is invalid key. 
   */
  void bindKey(byte key, byte to);

  /**
   * @throws InvalidConfigException when not all keys have bind.
   */
  const std::unordered_map<byte, byte>& getKeybinds() const;

 private:
  int memory_size_;
  int reserved_memory_size_;
  int stack_size_;
  int display_width_;
  int display_height_;
  int timer_frequency_;
  std::unordered_map<byte, byte> keybinds_;

  void validateKeybinds() const;
};

} // namespace chip8

#endif // CHIP8_CONFIGURATION_CONFIGURATION_H

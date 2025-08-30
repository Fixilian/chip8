#ifndef CHIP8_BASE_CONFIGURATION_H
#define CHIP8_BASE_CONFIGURATION_H

namespace chip8 {

class Configuration {
 public:
  static constexpr int kMemorySize = 4096;

  static constexpr int kReservedMemorySize = 512;

  static constexpr int kStackSize = 16;

  Configuration() {}

  Configuration(const Configuration&) = default;
  Configuration& operator=(const Configuration&) = default;
  Configuration(Configuration&&) = default;
  Configuration& operator=(Configuration&&) = default;
};

} // namespace chip8

#endif // CHIP8_BASE_CONFIGURATION_H

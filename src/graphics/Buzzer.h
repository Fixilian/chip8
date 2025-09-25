#ifndef CHIP8_GRAPHICS_BUZZER_H
#define CHIP8_GRAPHICS_BUZZER_H

namespace chip8 {

/**
 * Buzzer interface.
 */
class Buzzer {
 public:
  virtual ~Buzzer() {}

  virtual bool init() = 0;

  virtual void buzz() = 0;
};

} // namespace chip8

#endif // CHIP8_GRAPHICS_BUZZER_H

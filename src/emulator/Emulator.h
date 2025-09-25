#ifndef CHIP8_EMULATOR_EMULATOR_H
#define CHIP8_EMULATOR_EMULATOR_H

namespace chip8 {

class Emulator {
 public:
  Emulator() {}

  int run(int argc, char** argv);
};

} // namespace chip8

#endif // CHIP8_EMULATOR_EMULATOR_H

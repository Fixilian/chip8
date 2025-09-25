#include "emulator/Emulator.h"

using namespace chip8;

int main(int argc, char** argv) {
  Emulator emulator;
  emulator.run(argc, argv);
}

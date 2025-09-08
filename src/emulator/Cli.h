#ifndef CHIP8_EMULATOR_CLI_H
#define CHIP8_EMULATOR_CLI_H

#include "CommandLineArguments.h"

namespace chip8 {

/**
 * Parses command line arguments.
 * @param[out] err - > 0 if some error occur, otherwise = 0.
 */
CommandLineArguments parse(int argc, char** argv, int& err);

} // namespace chip8

#endif // CHIP8_EMULATOR_CLI_H

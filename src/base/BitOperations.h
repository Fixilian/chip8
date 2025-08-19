#ifndef CHIP8_BITOPERATIONS_H
#define CHIP8_BITOPERATIONS_H

#include "Aliases.h"

namespace chip8 {

word highest4BitsOf(word op);

word lowest12BitsOf(word op);

word lowest8BitsOf(word op);

word lowest4BitsOf(word op);

/**
 * Returns lower 4 bits of the high byte of opcode.
 * @returns lower 4 bits of the high byte of opcode.
 */
word getXFrom(word op);

/**
 * Returns upper 4 bits of the low byte of opcode.
 * @returns upper 4 bits of the low byte of opcode.
 */
word getYFrom(word op);

} // namespace chip8

#endif // CHIP8_BITOPERATIONS_H

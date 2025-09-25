#ifndef CHIP8_BITOPERATIONS_H
#define CHIP8_BITOPERATIONS_H

#include <cstddef>

#include "Aliases.h"

namespace chip8 {

constexpr std::size_t kBits = 8;

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

byte leastSignificantBitOf(byte b);

byte mostSignificantBitOf(byte b);

/**
 * Returns bit at position pos.
 * Byte has following layout: 01234567, where byte[0] is most-significant bit.
 * @returns bit at position pos.
 */
byte getBit(byte b, std::size_t pos);

/**
 * Returns byte with bit set at given position pos.
 * Byte has following layout: 01234567, where byte[0] is most-significant bit.
 * @returns byte with bit set at given position pos.
 */
byte setBit(byte b, std::size_t pos, byte val);


/**
 * Writes Binary-Coded Decimal representation of b to dst1, dst2, dst3.
 * Places hundreds digit in dst1, tens digit in dst2, ones digit in dst3. 
 */
void writeBcdOf(byte b, byte& dst1, byte& dst2, byte& dst3);


} // namespace chip8

#endif // CHIP8_BITOPERATIONS_H

#ifndef CHIP8_BASE_FILEIO_H
#define CHIP8_BASE_FILEIO_H

#include <string>

#include "Aliases.h"
#include "Rom.h"

namespace chip8 {

/**
 * Reads entire file into string.
 * @throws IOException
 */
std::string readFile(const std::string& name, int max_size);

/**
 * Reads rom from file.
 * @throws IOException
 */
Rom fromFile(const std::string& name, int max_size);

/**
 * Writes src to file.
 * @throws IOException
 */
void writeFile(const std::string& name, const std::string& src);

} // namespace chip8

#endif // CHIP8_BASE_FILEIO_H

#ifndef CHIP8_CONFIGURATION_JSONCONFIG_H
#define CHIP8_CONFIGURATION_JSONCONFIG_H

#include <string>

#include "Config.h"

namespace chip8 {

/**
 * Reads config from json string.
 * @throws InvalidConfigException when s contains invalid config.
 */
Config readFromJson(const std::string& s);

/**
 * Serializes default config to json string.
 */
std::string defaultConfig();

/**
 * Serializes config to json string.
 */
std::string toJson(const Config& cfg);

} // namespace chip8

#endif // CHIP8_CONFIGURATION_JSONCONFIG_H

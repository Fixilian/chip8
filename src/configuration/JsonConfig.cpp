#include "JsonConfig.h"

#include <exception>
#include <nlohmann/json.hpp>
#include <unordered_map>

#include "exception/InvalidConfigException.h"
#include "exception/UnknownKeyException.h"

using namespace std;

namespace chip8 {

using json = nlohmann::json;


static KeybindTable readKeybinds(json& j) {
  KeybindTable binds;
  if (j.contains("quit_key")) {
    string quit_key = j["quit_key"].template get<string>();
    binds.setQuitKey(KeybindTable::stringToKeyCode(quit_key));
  }
  if (j.contains("keybinds")) {
    auto str_binds = j["keybinds"].template get<unordered_map<string, byte>>();
    for (const auto&[key, to] : str_binds) {
      binds.bindKey(key, to);
    }
  }
  return binds;
}


static void readSpecification(json& j, MachineSpecification& spec) {
  if (j.contains("memory_size")) {
    spec.setMemorySize(j["memory_size"].template get<int>());
  }
  if (j.contains("reserved_memory_size")) {
    spec.setReservedMemorySize(j["reserved_memory_size"].template get<int>());
  }
  if (j.contains("stack_size")) {
    spec.setStackSize(j["stack_size"].template get<int>());
  }
  if (j.contains("display_width")) {
    spec.setDisplayWidth(j["display_width"].template get<int>());
  }
  if (j.contains("display_height")) {
    spec.setDisplayHeight(j["display_height"].template get<int>());
  }
  if (j.contains("timer_frequency")) {
    spec.setTimerFrequency(j["timer_frequency"].template get<int>());
  }
}


static Config readConfig(const string& s) {
  json j = json::parse(s);
  MachineSpecification spec;
  if (j.contains("specification")) {
    readSpecification(j["specification"], spec);
  }
  if (j.contains("keybind_table")) {
    return Config(spec, readKeybinds(j["keybind_table"]));
  } else {
    return Config(spec);
  }
}


Config readFromJson(const string& s) {
  try {
    return readConfig(s);
  } catch (const exception& ex) {
    throw InvalidConfigException(ex.what());
  } 
}


string defaultConfig() {
  MachineSpecification spec;
  Config cfg(spec);
  return toJson(cfg);
}


static string keyToString(byte key) {
  byte minCommonKey = 33;
  byte maxCommonKey = 126;
  if (key >= minCommonKey && key <= maxCommonKey) {
    char ch = static_cast<char>(key);
    return string(1, ch); 
  } else {
    for (const auto&[alias, to] : KeybindTable::aliases) {
      if (key == to) {
        return alias;
      }
    }
  }
  throw UnknownKeyException(key, "Can not convert key to string");
}


static unordered_map<string, byte> getStringBinds(const KeybindTable& keybinds) {
  auto binds = keybinds.getTable();
  unordered_map<string, byte> string_binds;
  for (const auto&[key, to] : binds) {
    string_binds[keyToString(key)] = to;
  }
  return string_binds;
}


static void to_json(json& j, const Config &cfg) {
  auto spec = cfg.getSpecification();
  auto keybinds = cfg.getKeyBinds();
  auto string_binds = getStringBinds(keybinds);
  j = json{
    { "specification", {
        {"memory_size", spec.getMemorySize()},
        {"reserved_memory_size", spec.getReservedMemorySize()},
        {"stack_size", spec.getStackSize()},
        {"display_width", spec.getDisplayWidth()},
        {"display_height", spec.getDisplayHeight()},
        {"timer_frequency", spec.getTimerFrequency()},
      }
    },
    { "keybind_table", {
        {"quit_key", keyToString(keybinds.getQuitKey())},
        {"keybinds", string_binds},
      }
    },
  };
}


string toJson(const Config &cfg) {
  json j = cfg;
  int indent = 4;
  return j.dump(indent);
}


} // namespace chip8

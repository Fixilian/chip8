#include <gtest/gtest.h>

#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>

#include "configuration/JsonConfig.h"

using namespace std;
using namespace chip8;

using json = nlohmann::json;


TEST(JsonConfigTest, ReadFromJson) {
  // Arrange
  string s = 
    R"(
      { 
        "specification" : {
          "memory_size" : 8192,
          "reserved_memory_size" : 1024,
          "stack_size" : 32,
          "display_width" : 128,
          "display_height" : 64,
          "timer_frequency" : 144
        },                          
        "keybind_table" : {
          "quit_key" : "ESCAPE",
          "keybinds" : {
            "a" : 0,
            "b" : 1,
            "c" : 2,
            "d" : 3,
            "e" : 4,
            "f" : 5,
            "g" : 6,
            "h" : 7,
            "i" : 8,
            "j" : 9,
            "k" : 10,
            "l" : 11,
            "m" : 12,
            "n" : 13,
            "o" : 14,
            "p" : 15
          }
        }
      }
  )";
  int memory_size = 8192;
  int reserved_memory_size = 1024;
  int stack_size = 32;
  int display_width = 128;
  int display_height = 64;
  int timer_frequency = 144;
  string quit_key = "ESC";
  unordered_map<string, chip8::byte> binds;
  binds["A"] = 0x0;
  binds["B"] = 0x1;
  binds["C"] = 0x2;
  binds["D"] = 0x3;
  binds["E"] = 0x4;
  binds["F"] = 0x5;
  binds["G"] = 0x6;
  binds["H"] = 0x7;
  binds["I"] = 0x8;
  binds["J"] = 0x9;
  binds["K"] = 0xA;
  binds["L"] = 0xB;
  binds["M"] = 0xC;
  binds["N"] = 0xD;
  binds["O"] = 0xE;
  binds["P"] = 0xF;

  // Act
  Config cfg = readFromJson(s);

  // Assert
  auto& spec = cfg.getSpecification();
  EXPECT_EQ(spec.getMemorySize(), memory_size);
  EXPECT_EQ(spec.getReservedMemorySize(), reserved_memory_size);
  EXPECT_EQ(spec.getStackSize(), stack_size);
  EXPECT_EQ(spec.getDisplayWidth(), display_width);
  EXPECT_EQ(spec.getDisplayHeight(), display_height);
  EXPECT_EQ(spec.getTimerFrequency(), timer_frequency);
  auto& keybinds = cfg.getKeyBinds();
  auto& adapter = keybinds.getAdapter();
  for (const auto&[key, to] : binds) {
    EXPECT_EQ(keybinds[adapter.convert(key)], to);
  } 
}


TEST(JsonConfigTest, ToJson) {
  // Arrange
  MachineSpecification spec;
  Config cfg(spec);

  // Act
  string s = toJson(cfg);
  cout << s << '\n';

  // Assert
  json j = json::parse(s);
  EXPECT_TRUE(j.contains("specification"));
  EXPECT_TRUE(j["specification"].contains("memory_size"));
  EXPECT_TRUE(j["specification"].contains("reserved_memory_size"));
  EXPECT_TRUE(j["specification"].contains("stack_size"));
  EXPECT_TRUE(j["specification"].contains("display_width"));
  EXPECT_TRUE(j["specification"].contains("display_height"));
  EXPECT_TRUE(j["specification"].contains("timer_frequency"));

  EXPECT_TRUE(j.contains("keybind_table"));
  EXPECT_TRUE(j["keybind_table"].contains("quit_key"));
  EXPECT_TRUE(j["keybind_table"].contains("keybinds"));
}

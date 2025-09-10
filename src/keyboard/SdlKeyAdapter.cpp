#include "SdlKeyAdapter.h"

#include "exception/UnknownKeyException.h"

using namespace std;

namespace chip8 {

  
unordered_map<string, int> SdlKeyAdapter::key_table_ = {
  {"A", 4},
  {"B", 5},
  {"C", 6},
  {"D", 7},
  {"E", 8},
  {"F", 9},
  {"G", 10},
  {"H", 11},
  {"I", 12},
  {"J", 13},
  {"K", 14},
  {"L", 15},
  {"M", 16},
  {"N", 17},
  {"O", 18},
  {"P", 19},
  {"Q", 20},
  {"R", 21},
  {"S", 22},
  {"T", 23},
  {"U", 24},
  {"V", 25},
  {"W", 26},
  {"X", 27},
  {"Y", 28},
  {"Z", 29},

  {"1", 30},
  {"2", 31},
  {"3", 32},
  {"4", 33},
  {"5", 34},
  {"6", 35},
  {"7", 36},
  {"8", 37},
  {"9", 38},
  {"0", 39},

  {"RETURN", 40},
  {"ESCAPE", 41},
  {"BACKSPACE", 42},
  {"TAB", 43},
  {"SPACE", 44},

  {"-", 45},
  {"=", 46},
  {"[", 47},
  {"]", 48},
  {"\\", 49},

  {":", 51},
  {"'", 52},
  {",", 54},
  {".", 55},
  {"/", 56},
  
  {"CAPS", 57},

  {"F1", 58},
  {"F2", 59},
  {"F3", 60},
  {"F4", 61},
  {"F5", 62},
  {"F6", 63},
  {"F7", 64},
  {"F8", 65},
  {"F9", 66},
  {"F10", 67},
  {"F11", 68},
  {"F12", 69},

  {"PRINTSCREEN", 70},
  {"SCROLLLOCK", 71},
  {"PAUSE", 72},

  {"INSERT", 73},
  {"HOME", 74},
  {"PAGEUP", 75},
  {"DELETE", 76},
  {"END", 77},
  {"PAGEDOWN", 78},

  {"RIGHT", 79},
  {"LEFT", 80},
  {"DOWN", 81},
  {"UP", 82},
};


int SdlKeyAdapter::convert(const string& key) const {
  if (!key_table_.contains(key)) {
    throw UnknownKeyException(key[0], "Unknown key name");
  }
  return key_table_[key];
}


const string& SdlKeyAdapter::convert(int key) const {
  for (const auto&[alias, to] : key_table_) {
    if (key == to) {
      return alias;
    }
  }
  throw UnknownKeyException(key, "Unknown key");
}


} // namespace chip8;

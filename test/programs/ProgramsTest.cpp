#include <gtest/gtest.h>

#include <chrono>
#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "base/Endian.h"
#include "base/FileIO.h"
#include "execution/Cpu.h"
#include "instruction/ExecutionContext.h"
#include "TestObjectFactory.h"

using namespace std;
using namespace chip8;


using Callback = function<void(Cpu&, KeyboardMonitor&)>;


class ProgramTest : public testing::Test {
 protected:

  bool test(
    const string& rom_file, 
    const string& expected_file, 
    chip8::byte mode, 
    Callback& cpu_terminate) 
  {
    // Arrange
    string dir = "roms/";
    string rom_path = dir + rom_file;
    string expected_path = dir + expected_file;
    int mem_size = 4096;
    int mem_reserve = 512;
    int frame_w = 64;
    int frame_h = 32;
    int stack_size = 16;
    Rom rom = fromFile(rom_path, mem_size);
    auto keyboard = createKeyboardMonitor();
    auto mem = createMemory(mem_size, mem_reserve);
    ExecutionContext ctx(stack_size, frame_w, frame_h, *mem, *keyboard); 
    Cpu cpu(*mem, ctx, Endianness::BigEndian);
    vector<int> expected = readResultFile(expected_path, 1024 + frame_h * frame_w);
    thread t;
    if (mode > 0) {
      word addr = 0x1FF;
      mem->setSysMemoryProtectionEnabled(false);
      (*mem)[addr] = mode;
      mem->setSysMemoryProtectionEnabled(true);
      t = thread([&cpu, &keyboard, &cpu_terminate]() {
        cpu_terminate(cpu, *keyboard);
      });
    }

    // Act
    cpu.execute(rom);

    // Assert
    if (t.joinable()) {
      t.join();
    }
    bool result = check(ctx.frame, expected);
    return result;
  }

  bool test(const string& rom_file, const string& expected_file) {
    Callback callback = [] (Cpu&, KeyboardMonitor&) {};
    return test(rom_file, expected_file, 0, callback);
  }

  vector<int> readResultFile(const string& filename, int max_size) {
    string s = readFile(filename, max_size);
    char zero_ch = '-';
    char one_ch = '0';
    vector<int> data;

    for (size_t i = 0; i < s.length(); i += 1) {
      char ch = s[i];
      if (ch == one_ch) {
        data.push_back(1);
      } else if (ch == zero_ch) {
        data.push_back(0);
      }
    }
    return data;
  }

  bool check(const Frame& f, vector<int>& expected) {
    int h = f.getHeight();
    int w = f.getWidth();
    for (int y = 0; y < h; y += 1) {
      for (int x = 0; x < w; x += 1) {
        int epixel = expected[x + y * w];
        int fpixel = f.getPixel(x, y);
        if (epixel != fpixel) {
          cout << f.toString() << '\n';
          return false;
        }
      }
    }
    return true;
  }
};


TEST_F(ProgramTest, Correctness) {
  // Arrange
  vector<pair<string, string>> roms = {
    {"logo.ch8", "logo.txt"},
    {"ibm_logo.ch8", "ibm_logo.txt"},
    {"corax+.ch8", "corax+.txt"},
    {"flags.ch8", "flags.txt"},
  };
  vector<bool> actual;

  // Act
  for (const auto&[rom_src, expected_src] : roms) {
    bool result = test(rom_src, expected_src);
    actual.push_back(result);
  }

  // Assert
  for (bool x : actual) {
    EXPECT_TRUE(x);
  }
}


TEST_F(ProgramTest, Quirks) {
  // Arrange
  string rom_src = "quirks.ch8";
  string expected_src = "quirks.txt";
  vector<bool> actual;
  chip8::byte mode = 1; // choose CHIP8
  Callback callback = [] (Cpu& cpu, KeyboardMonitor& keyboard) {
    chrono::seconds interval{4};
    this_thread::sleep_for(interval);
    keyboard.onKeyPressed(0xF);
    keyboard.onKeyReleased(0xF);
    cpu.stop();
  };

  // Act
  bool result = test(rom_src, expected_src, mode, callback);

  // Assert
  EXPECT_TRUE(result);
}

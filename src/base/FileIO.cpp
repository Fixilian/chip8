#include "FileIO.h"

#include <fstream>
#include <vector>

#include "exception/IOException.h"

using namespace std;

namespace chip8 {


static streamsize fileSize(ifstream& file) {
  file.seekg(0, ios::end);
  streamsize file_size = file.tellg();
  file.seekg(0, ios::beg);
  return file_size;
} 


string readFile(const string& name, int max_size) {
  ifstream file(name, ios::binary);
  if (!file) {
    throw IOException("Cannot open file: " + name);
  }

  auto file_size = fileSize(file);
  if (max_size > 0 && file_size > max_size) {
    throw IOException("File exceeds max_size: " + name);
  }

  string content(static_cast<size_t>(file_size), '\0');
  if (!file.read(content.data(), file_size)) {
    throw IOException("Failed to read file: " + name);
  }

  return content;
}


Rom fromFile(const string& name, int max_size) {
  ifstream file(name, std::ios::binary);
  if (!file) {
    throw IOException("Cannot open file: " + name);
  }

  auto file_size = fileSize(file);
  if (max_size > 0 && file_size > max_size) {
      throw IOException("File exceeds max_size: " + name);
  }
  if (file_size % sizeof(word) != 0) {
      throw IOException("ROM file size is not aligned to word size");
  }

  int word_count = static_cast<int>(file_size / sizeof(word));
  vector<word> buffer(word_count);
  if (!file.read(reinterpret_cast<char*>(buffer.data()), file_size)) {
      throw IOException("Failed to read file: " + name);
  }

  return Rom(buffer.data(), static_cast<int>(file_size));
}


void writeFile(const string& name, const string& src) {
  ofstream file(name, ios::binary);
  if (!file) {
    throw IOException("Cannot open file for writing: " + name);
  }

  file.write(src.data(), static_cast<streamsize>(src.size()));
  if (!file) {
    throw IOException("Failed to write to file: " + name);
  }
}


} // namespace chip8

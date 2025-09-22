#include "ThreadRegistry.h"

using namespace std;

namespace chip8 {


thread_local string ThreadRegistry::name_ = "";


void ThreadRegistry::setThreadName(const string& name) {
  name_ = name;
}


const string& ThreadRegistry::getThreadName() {
  return name_;
}


} // namespace chip8

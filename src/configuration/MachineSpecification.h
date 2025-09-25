#ifndef CHIP8_CONFIGURATION_MACHINESPECIFICATION_H
#define CHIP8_CONFIGURATION_MACHINESPECIFICATION_H

namespace chip8 {

/**
 * Machine specification.
 * Contains most of the machine parameters. 
 * Every set function throw InvalidArgumentException.
 */
class MachineSpecification {
 public:
  MachineSpecification();

  MachineSpecification(const MachineSpecification&) = default;
  MachineSpecification& operator=(const MachineSpecification&) = default;
  MachineSpecification(MachineSpecification&&) = default;
  MachineSpecification& operator=(MachineSpecification&&) = default;

  void setMemorySize(int size);
  int getMemorySize() const;

  void setReservedMemorySize(int size);
  int getReservedMemorySize() const;

  void setStackSize(int size);
  int getStackSize() const;

  void setDisplayWidth(int width);
  int getDisplayWidth() const;

  void setDisplayHeight(int height);
  int getDisplayHeight() const;

  void setTimerFrequency(int freq);
  int getTimerFrequency() const;

 private:
  int memory_size_;
  int reserved_memory_size_;
  int stack_size_;
  int display_width_;
  int display_height_;
  int timer_frequency_;
};

} // namespace chip8

#endif // CHIP8_CONFIGURATION_MACHINESPECIFICATION_H

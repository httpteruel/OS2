#ifndef MY_LIB_H
#define MY_LIB_H

#include <string>
#include <vector>
#include <cstdint>

std::vector<uint16_t> loadBinary(const std::string& filename);
void writeMemory(uint16_t address, uint16_t value);
uint16_t readMemory(uint16_t address);

#endif // MY_LIB_H
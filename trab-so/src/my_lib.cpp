#include "my_lib.h"
#include <fstream>

std::vector<uint16_t> loadBinary(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    std::vector<uint16_t> instructions;
    uint16_t instruction;
    while (file.read(reinterpret_cast<char*>(&instruction), sizeof(uint16_t))) {
        instructions.push_back(instruction);
    }
    return instructions;
}

void writeMemory(uint16_t address, uint16_t value) {
    // Simulação: no ambiente do professor, isso escreveria na memória real
    // Aqui, apenas simulamos
}

uint16_t readMemory(uint16_t address) {
    // Simulação: no ambiente do professor, isso leria da memória real
    return 0; // Placeholder
}
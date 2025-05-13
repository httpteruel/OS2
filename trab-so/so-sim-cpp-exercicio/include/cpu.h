#ifndef CPU_H
#define CPU_H

#include <cstdint>
#include <vector>

class Cpu {
public:
    void writePort(uint32_t port, uint32_t value);
    uint32_t readPort(uint32_t port);
    void writeMemory(uint32_t address, uint32_t value);
    uint32_t readMemory(uint32_t address);
    void setBaseLimit(uint32_t base, uint32_t limit);
    uint32_t checkInterrupts();
    void executeNextInstruction();
    uint32_t getRegister(uint32_t index);
    void setRegister(uint32_t index, uint32_t value);
    void setProgramCounter(uint32_t pc);
    uint32_t getProgramCounter();
    std::vector<uint32_t> getRegisters();
    void setRegisters(const std::vector<uint32_t>& regs);
};

#endif // CPU_H
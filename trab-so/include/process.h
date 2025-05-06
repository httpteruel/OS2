#ifndef PROCESS_H
#define PROCESS_H

#include "cpu.h"
#include "memory_manager.h"
#include <string>
#include <vector>

enum ProcessState { Ready, Running, Terminated };

class Process {
private:
    int pid;
    ProcessState state;
    Cpu cpu;
    std::string binaryFile;
    uint16_t memorySize;
    std::vector<uint16_t> instructions; // Armazena instruções carregadas via my-lib

public:
    Process(int id, const std::string& bin, uint16_t memSize);
    int getPid() const;
    ProcessState getState() const;
    void setState(ProcessState s);
    Cpu& getCpu();
    std::string getBinaryFile() const;
    uint16_t getMemorySize() const;
    const std::vector<uint16_t>& getInstructions() const;
};

#endif // PROCESS_H
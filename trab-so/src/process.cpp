#include "process.h"
#include "my_lib.h"

Process::Process(int id, const std::string& bin, uint16_t memSize) 
    : pid(id), state(Ready), binaryFile(bin), memorySize(memSize), instructions(loadBinary(bin)) {}

int Process::getPid() const { return pid; }
ProcessState Process::getState() const { return state; }
void Process::setState(ProcessState s) { state = s; }
Cpu& Process::getCpu() { return cpu; }
std::string Process::getBinaryFile() const { return binaryFile; }
uint16_t Process::getMemorySize() const { return memorySize; }
const std::vector<uint16_t>& Process::getInstructions() const { return instructions; }
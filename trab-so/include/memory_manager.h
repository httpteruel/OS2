#ifndef MEMORY_MANAGER_H  // gestão de memória e PID
#define MEMORY_MANAGER_H

#include <vector>
#include <cstdint>

class MemoryManager {
private:
    struct MemoryBlock {
        int pid;
        uint16_t base;
        uint16_t size;
        MemoryBlock(int p, uint16_t b, uint16_t s) : pid(p), base(b), size(s) {}
    };
    std::vector<MemoryBlock> blocks;
    uint16_t totalMemory;
    uint16_t nextBase;

public:
    MemoryManager(uint16_t size);
    bool allocate(int pid, uint16_t size);
    void deallocate(int pid);
    uint16_t getBase(int pid);
    uint16_t getSize(int pid);
};

#endif
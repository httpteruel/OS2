#ifndef OS_SIMULATOR_H
#define OS_SIMULATOR_H

#include "process.h"
#include "memory_manager.h"
#include <vector>
#include <string>

class OSSimulator {
private:
    std::vector<Process> processes;
    Process* currentProcess;
    bool running;
    MemoryManager memoryManager;

public:
    OSSimulator();
    void loadProcess(const std::string& filename);
    void systemCall();
    void handleKeyboardInterrupt(char c);
    void run();
};

#endif
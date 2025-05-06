#include "memory_manager.h" // alocar endereços ao PID

MemoryManager::MemoryManager(uint16_t size) : totalMemory(size), nextBase(0) {}

bool MemoryManager::allocate(int pid, uint16_t size) {
    if (nextBase + size > totalMemory) {
        return false; // Sem espaço
    }
    blocks.emplace_back(pid, nextBase, size);
    nextBase += size;
    return true;
}

void MemoryManager::deallocate(int pid) { // desalocar memoria
    for (auto it = blocks.begin(); it != blocks.end(); ++it) {
        if (it->pid == pid) {
            blocks.erase(it);
            return;
        }
    }
}

uint16_t MemoryManager::getBase(int pid) { // pegar informações 
    for (const auto& block : blocks) {
        if (block.pid == pid) {
            return block.base;
        }
    }
    return 0;
}

uint16_t MemoryManager::getSize(int pid) {
    for (const auto& block : blocks) {
        if (block.pid == pid) {
            return block.size;
        }
    }
    return 0;
}
#include "os.h"

namespace MemoryManager {
    void initialize() {
        // Configura memória virtual como base-limite
        OS::cpu->set_vmem_mode(VmemMode::BaseLimit);
    }
    
    void set_process_memory(Process& proc) {
        OS::cpu->set_vmem_paddr_base(proc.vmem_base);
        OS::cpu->set_vmem_size(proc.vmem_size);
        
        // Carrega memória do processo na memória física
        for (size_t i = 0; i < proc.memory.size(); i++) {
            OS::cpu->pmem_write(proc.vmem_base + i, proc.memory[i]);
        }
    }
}
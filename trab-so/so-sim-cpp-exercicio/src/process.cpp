#include "os.h"

namespace ProcessManager {
    static uint16_t next_pid = 1;
    
    void create_process(const std::string& fname) {
        Process* proc = new Process();
        proc->pid = next_pid++;
        proc->active = true;
        proc->pc = 0;
        for (int i = 0; i < 8; i++) proc->gpr[i] = 0;
        
        // Carrega o binário
        proc->memory = Lib::load_from_disk_to_16bit_buffer(fname);
        proc->vmem_size = proc->memory.size();
        proc->vmem_base = 0x1000; // Endereço base fixo (exemplo)
        
        MemoryManager::set_process_memory(*proc);
        OS::current_process = proc;
        
        // Configura CPU
        OS::cpu->set_pc(proc->pc);
        for (int i = 0; i < 8; i++) OS::cpu->set_gpr(i, proc->gpr[i]);
    }
    
    void switch_to_idle() {
        if (!OS::current_process) {
            OS::current_process = &OS::idle_process;
            MemoryManager::set_process_memory(OS::idle_process);
            OS::cpu->set_pc(OS::idle_process.pc);
            for (int i = 0; i < 8; i++) {
                OS::cpu->set_gpr(i, OS::idle_process.gpr[i]);
            }
        }
    }
}
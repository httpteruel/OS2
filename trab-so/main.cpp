#include "os.h"

int main() {
    OS::initialize();
    
    // Loop principal do simulador
    while (true) {
        // Executa uma instrução da CPU (método fornecido pela classe Cpu)
        OS::cpu->execute_instruction();
        
        // Verifica interrupções
        if (OS::cpu->has_interrupt()) {
            uint8_t int_code = OS::cpu->get_interrupt_code();
            OS::handle_interrupt(int_code);
        }
        
        // Verifica chamadas de sistema
        if (OS::cpu->has_syscall()) {
            OS::handle_syscall();
        }
    }
    
    return 0;
}
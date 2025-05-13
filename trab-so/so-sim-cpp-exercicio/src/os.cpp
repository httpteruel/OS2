#include "os.h"
#include <iostream>

namespace OS {
    Cpu* cpu; // Ponteiro para a classe Cpu (fornecida)
    Process* current_process; // Processo atual
    Process idle_process;    // Processo ocioso
–
    void initialize() {
        cpu = new Cpu(); // Inicializa a CPU (fornecida pelo repositório)
        MemoryManager::initialize();
        Terminal::initialize();
        
        // Carrega o processo ocioso (idle.bin)
        ProcessManager::create_process("idle.bin");
        idle_process = *current_process;
        current_process = nullptr;
        
        // Configura modo de memória virtual como BaseLimit
        cpu->set_vmem_mode(VmemMode::BaseLimit);
        
        std::cout << "Sistema operacional inicializado\n";
    }
    
    void handle_interrupt(uint8_t code) {
        switch (code) {
            case 0: // Keyboard
                uint16_t c = cpu->read_io(IO_Port::TerminalReadTypedChar);
                Terminal::process_input(static_cast<char>(c));
                break;
            case 3: // CpuException
                CpuException ex = cpu->get_cpu_exception();
                if (ex.code == 0) { // VmemPageFault (GPF)
                    std::cout << "GPF: Acesso a memória inválida\n";
                    kill_process();
                    ProcessManager::switch_to_idle();
                }
                break;
        }
    }
    
    void handle_syscall() {
        uint16_t syscall_code = cpu->get_gpr(0);
        switch (syscall_code) {
            case 0: // Encerrar processo
                kill_process();
                ProcessManager::switch_to_idle();
                break;
            case 1: // Imprimir string
                {
                    uint16_t addr = cpu->get_gpr(1);
                    std::string s;
                    for (uint16_t i = addr; ; i++) {
                        uint16_t c = cpu->pmem_read(current_process->vmem_base + i);
                        if (c == 0) break;
                        s += static_cast<char>(c);
                    }
                    Terminal::print_string(s, 3); // Terminal App
                }
                break;
            case 2: // Nova linha
                Terminal::print_string("\n", 3);
                break;
            case 3: // Imprimir inteiro
                {
                    uint16_t num = cpu->get_gpr(1);
                    Terminal::print_string(std::to_string(num), 3);
                }
                break;
        }
    }
    
    void load_program(const std::string& fname) {
        ProcessManager::create_process(fname);
    }
    
    void kill_process() {
        if (current_process) {
            current_process->active = false;
            current_process = nullptr;
        }
    }
    
    void shutdown() {
        std::cout << "Encerrando simulador\n";
        delete cpu;
        exit(0);
    }
    
    void execute_terminal_command(const std::string& cmd) {
        if (cmd == "shutdown") {
            shutdown();
        } else if (cmd.substr(0, 4) == "load ") {
            load_program(cmd.substr(5));
        } else if (cmd == "kill") {
            kill_process();
            ProcessManager::switch_to_idle();
        } else {
            Terminal::print_string("Comando inválido\n", 2); // Terminal Command
        }
    }
}
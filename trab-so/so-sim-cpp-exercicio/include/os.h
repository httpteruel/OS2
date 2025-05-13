#ifndef OS_H
#define OS_H

#include <cstdint>
#include <vector>
#include <string>
#include "cpu.h" // Fornecido pelo repositório so-sim-cpp-exercicio
#include "lib.h" // Fornecido pelo repositório my-lib

// Modos de memória virtual (conforme documento)
enum VmemMode {
    Disabled = 0,
    BaseLimit = 1,
    Paging = 2
};

// Estrutura do processo
struct Process {
    uint16_t pid;              // Identificador do processo
    uint16_t pc;               // Program Counter
    uint16_t gpr[8];           // Registradores de propósito geral (r0-r7)
    uint16_t vmem_base;        // Endereço base da memória virtual
    uint16_t vmem_size;        // Tamanho da memória virtual
    bool active;               // Estado do processo (ativo ou não)
    std::vector<uint16_t> memory; // Memória alocada para o processo
};

// Funções do sistema operacional
namespace OS {
    void initialize();                     // Inicializa o sistema
    void handle_interrupt(uint8_t code);   // Trata interrupções
    void handle_syscall();                 // Trata chamadas de sistema
    void load_program(const std::string& fname); // Carrega um programa
    void kill_process();                   // Mata o processo atual
    void shutdown();                      // Encerra o simulador
    void execute_terminal_command(const std::string& cmd); // Executa comandos do terminal
}

// Funções de gerenciamento de processos
namespace ProcessManager {
    void create_process(const std::string& fname); // Cria um novo processo
    void switch_to_idle();                        // Alterna para o processo ocioso
}

// Funções de gerenciamento de memória
namespace MemoryManager {
    void initialize();                     // Configura memória virtual
    void set_process_memory(Process& proc); // Define base-limite para o processo
}

// Funções do terminal
namespace Terminal {
    void initialize();                     // Inicializa o terminal
    void process_input(char c);            // Processa entrada do teclado
    void print_string(const std::string& s, uint8_t term_code); // Imprime string no terminal
}

#endif
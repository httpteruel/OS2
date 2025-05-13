#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <stdexcept>
#include "lib.h"
#include "cpu.h"

const uint32_t PORT_TERMINAL_SET = 0x1000;
const uint32_t PORT_TERMINAL_UPLOAD = 0x1001;
const uint32_t PORT_TERMINAL_READ_TYPED_CHAR = 0x1002;
const uint32_t IRQ_KEYBOARD = 0x01;
const uint32_t IRQ_SYSCALL = 0x02;
const uint32_t IRQ_GPF = 0x03;
const uint32_t SUBTERMINAL_1_CODE = 0x01;
const uint32_t MEMORY_BASE_ADDRESS = 0x0000;
const uint32_t MAX_MEMORY_SIZE = 0x10000;

enum class ProcessState { READY, RUNNING, TERMINATED };

struct Process {
    uint32_t pid;
    ProcessState state;
    uint32_t base;
    uint32_t limit;
    uint32_t pc;
    std::vector<uint32_t> regs;
    std::string binaryName;
};

class OperatingSystem {
private:
    Cpu& cpu;
    std::vector<Process> processes;
    Process* currentProcess;
    std::string commandBuffer;
    bool running;

    Process* loadBinary(const std::string& filename) {
        try {
            uint32_t size = Lib::get_file_size_words(filename);
            if (size == 0 || size * 2 > MAX_MEMORY_SIZE) {
                writeToTerminal("Erro: Tamanho inválido para " + filename + "\n");
                return nullptr;
            }
            std::vector<uint16_t> buffer = Lib::load_from_disk_to_16bit_buffer(filename);
            for (uint32_t i = 0; i < buffer.size(); ++i) {
                cpu.writeMemory(MEMORY_BASE_ADDRESS + i * 2, buffer[i]);
            }
            Process proc;
            proc.pid = processes.size() + 1;
            proc.state = ProcessState::READY;
            proc.base = MEMORY_BASE_ADDRESS;
            proc.limit = size * 2;
            proc.pc = MEMORY_BASE_ADDRESS;
            proc.regs = std::vector<uint32_t>(16, 0);
            proc.binaryName = filename;
            processes.push_back(proc);
            writeToTerminal("Programa '" + filename + "' carregado (PID: " + std::to_string(proc.pid) + ")\n");
            return &processes.back();
        } catch (const std::exception& e) {
            writeToTerminal("Erro ao carregar " + filename + ": " + e.what() + "\n");
            return nullptr;
        }
    }

    void writeToTerminal(const std::string& text) {
        cpu.writePort(PORT_TERMINAL_SET, SUBTERMINAL_1_CODE);
        for (char c : text) {
            cpu.writePort(PORT_TERMINAL_UPLOAD, static_cast<uint32_t>(c));
        }
    }

    void processCommand(const std::string& cmd) {
        if (cmd == "fechar") {
            writeToTerminal("Encerrando simulador...\n");
            running = false;
        } else if (cmd.substr(0, 9) == "carregar ") {
            std::string filename = cmd.substr(9);
            if (currentProcess && currentProcess->binaryName != "idle.bin") {
                writeToTerminal("Erro: Já existe um programa em execução\n");
            } else {
                Process* proc = loadBinary(filename);
                if (proc) {
                    terminateCurrentProcess();
                    currentProcess = proc;
                    currentProcess->state = ProcessState::RUNNING;
                    cpu.setBaseLimit(proc->base, proc->limit);
                    cpu.setProgramCounter(proc->pc);
                }
            }
        } else if (cmd == "matar") {
            if (currentProcess && currentProcess->binaryName != "idle.bin") {
                writeToTerminal("Programa '" + currentProcess->binaryName + "' terminado\n");
                terminateCurrentProcess();
                startIdleProcess();
            } else {
                writeToTerminal("Nenhum programa para matar\n");
            }
        } else {
            writeToTerminal("Comando desconhecido: " + cmd + "\n");
        }
    }

    void terminateCurrentProcess() {
        if (currentProcess) {
            currentProcess->state = ProcessState::TERMINATED;
            currentProcess = nullptr;
        }
    }

    void startIdleProcess() {
        if (!currentProcess) {
            currentProcess = loadBinary("idle.bin");
            if (currentProcess) {
                currentProcess->state = ProcessState::RUNNING;
                cpu.setBaseLimit(currentProcess->base, currentProcess->limit);
                cpu.setProgramCounter(currentProcess->pc);
            }
        }
    }

    void handleSyscall(uint32_t syscallNumber) {
        if (!currentProcess) return;
        switch (syscallNumber) {
            case 0:
                writeToTerminal("Programa '" + currentProcess->binaryName + "' terminou\n");
                terminateCurrentProcess();
                startIdleProcess();
                break;
            case 1:
                {
                    uint32_t charCode = cpu.getRegister(0);
                    writeToTerminal(std::string(1, static_cast<char>(charCode)));
                }
                break;
            case 2:
                {
                    uint32_t charCode = cpu.readPort(PORT_TERMINAL_READ_TYPED_CHAR);
                    cpu.setRegister(0, charCode);
                }
                break;
            case 3:
                cpu.setRegister(0, currentProcess->pid);
                break;
            default:
                writeToTerminal("Chamada de sistema inválida: " + std::to_string(syscallNumber) + "\n");
        }
    }

public:
    OperatingSystem(Cpu& cpu) : cpu(cpu), currentProcess(nullptr), running(true) {
        startIdleProcess();
        writeToTerminal("Sistema Operacional Monotarefa Iniciado\n");
    }

    void run() {
        while (running) {
            uint32_t interrupt = cpu.checkInterrupts();
            if (interrupt != 0) {
                if (interrupt == IRQ_KEYBOARD) {
                    uint32_t charCode = cpu.readPort(PORT_TERMINAL_READ_TYPED_CHAR);
                    char c = static_cast<char>(charCode);
                    if (c == '\n') {
                        processCommand(commandBuffer);
                        commandBuffer.clear();
                    } else if (c == '\r') {
                        commandBuffer.clear();
                        writeToTerminal("\r");
                    } else {
                        commandBuffer += c;
                        writeToTerminal(std::string(1, c));
                    }
                } else if (interrupt == IRQ_SYSCALL) {
                    uint32_t syscallNumber = cpu.getRegister(0);
                    handleSyscall(syscallNumber);
                } else if (interrupt == IRQ_GPF) {
                    writeToTerminal("GPF: Falha de proteção geral (PID: " + 
                        (currentProcess ? std::to_string(currentProcess->pid) : "nenhum") + ")\n");
                    terminateCurrentProcess();
                    startIdleProcess();
                }
            }
            if (currentProcess && currentProcess->state == ProcessState::RUNNING) {
                try {
                    cpu.executeNextInstruction();
                } catch (const std::exception& e) {
                    writeToTerminal("Exceção: " + std::string(e.what()) + "\n");
                    terminateCurrentProcess();
                    startIdleProcess();
                }
            }
        }
    }
};

int main() {
    try {
        Cpu cpu;
        OperatingSystem os(cpu);
        os.run();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Erro fatal: " << e.what() << std::endl;
        return 1;
    }
}
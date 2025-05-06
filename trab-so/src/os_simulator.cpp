#include "os_simulator.h"
#include "my_lib.h"
#include <iostream>
#include <sstream>

OSSimulator::OSSimulator() : currentProcess(nullptr), running(false), memoryManager(65535) {
    processes.emplace_back(0, "idle.bin", 1024);
    memoryManager.allocate(0, 1024);
}

void OSSimulator::loadProcess(const std::string& filename) {
    uint16_t memSize = 4096;
    int newPid = processes.size();
    if (memoryManager.allocate(newPid, memSize)) {
        processes.emplace_back(newPid, filename, memSize);
        std::cout << "Processo " << newPid << " carregado: " << filename 
                  << " (Memoria: " << memSize << " bytes, Base: " 
                  << memoryManager.getBase(newPid) << ")\n";
    } else {
        std::cout << "Erro: Sem memoria para carregar " << filename << "\n";
    }
}

void OSSimulator::systemCall() {
    uint16_t code = currentProcess->getCpu().get_gpr(0);
    switch (code) {
        case 0: // Terminar processo
            currentProcess->setState(Terminated);
            memoryManager.deallocate(currentProcess->getPid());
            currentProcess = &processes[0];
            std::cout << "Processo terminado. Executando idle.bin\n";
            break;
        case 1: // Ler da memoria (usando my-lib)
            {
                uint16_t index = currentProcess->getCpu().get_gpr(1);
                const auto& instructions = currentProcess->getInstructions();
                if (index < instructions.size()) {
                    uint16_t value = instructions[index]; // Lê do vetor carregado
                    std::cout << "Syscall 1: Lido da memoria (indice " << index << "): " << value << "\n";
                } else {
                    // No ambiente do professor, usaria readMemory
                    uint16_t base = memoryManager.getBase(currentProcess->getPid());
                    uint16_t address = base + index;
                    uint16_t value = readMemory(address);
                    std::cout << "Syscall 1: Lido da memoria (endereco " << address << "): " << value << "\n";
                }
            }
            break;
        case 2: // Escrever na memoria (usando my-lib)
            {
                uint16_t index = currentProcess->getCpu().get_gpr(1);
                uint16_t value = currentProcess->getCpu().get_gpr(2);
                auto& instructions = const_cast<std::vector<uint16_t>&>(currentProcess->getInstructions());
                if (index < instructions.size()) {
                    instructions[index] = value; // Escreve no vetor carregado
                    std::cout << "Syscall 2: Escrito na memoria (indice " << index << "): " << value << "\n";
                } else {
                    // No ambiente do professor, usaria writeMemory
                    uint16_t base = memoryManager.getBase(currentProcess->getPid());
                    uint16_t address = base + index;
                    writeMemory(address, value);
                    std::cout << "Syscall 2: Escrito na memoria (endereco " << address << "): " << value << "\n";
                }
            }
            break;
        case 3: // Imprimir valor de gpr[1]
            std::cout << currentProcess->getCpu().get_gpr(1) << "\n";
            break;
        default:
            std::cout << "Syscall invalida\n";
            break;
    }
}

void OSSimulator::handleKeyboardInterrupt(char c) {
    std::cout << "Tecla pressionada: " << c << "\n";
}

void OSSimulator::run() {
    running = true;
    currentProcess = &processes[0];
    std::cout << "Simulador iniciado. Executando idle.bin\n";

    std::string command;
    while (running) {
        std::cout << "> ";
        std::getline(std::cin, command);

        if (command == "exit") {
            running = false;
        } else if (command.substr(0, 5) == "load ") {
            loadProcess(command.substr(5));
            if (memoryManager.getBase(processes.back().getPid()) != 0) {
                currentProcess = &processes.back();
            }
        } else if (command == "kill") {
            systemCall();
        } else if (command == "execute") {
            if (currentProcess->getPid() == 0) {
                std::cout << "Nao e possivel executar idle.bin\n";
            } else {
                const auto& instructions = currentProcess->getInstructions();
                std::cout << "Executando " << currentProcess->getBinaryFile() << " (" << instructions.size() << " instrucoes)\n";
                for (uint16_t i = 0; i < instructions.size(); ++i) {
                    currentProcess->getCpu().set_pc(i);
                    std::cout << "Instrucao " << i << ": " << instructions[i] << "\n";
                }
                std::cout << "Execucao concluida\n";
            }
        } else if (command.substr(0, 7) == "syscall") {
            std::istringstream iss(command);
            std::string cmd;
            int code;
            iss >> cmd >> code;
            if (iss.fail() || code < 0 || code > 3) {
                std::cout << "Uso: syscall <0-3>\n";
            } else {
                currentProcess->getCpu().set_gpr(0, code);
                if (code == 1 || code == 2) {
                    currentProcess->getCpu().set_gpr(1, 5);
                    if (code == 2) {
                        currentProcess->getCpu().set_gpr(2, 42);
                    }
                }
                systemCall();
            }
        } else {
            std::cout << "Comando invalido\n";
        }
    }
}
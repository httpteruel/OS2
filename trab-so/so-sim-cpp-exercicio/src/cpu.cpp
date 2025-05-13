#include "cpu.h"
#include <stdexcept>

void Cpu::writePort(uint32_t port, uint32_t value) {
    // Implementação fictícia: escrever em uma porta
    throw std::runtime_error("writePort not implemented");
}

uint32_t Cpu::readPort(uint32_t port) {
    // Implementação fictícia: ler de uma porta
    throw std::runtime_error("readPort not implemented");
    return 0;
}

void Cpu::writeMemory(uint32_t address, uint32_t value) {
    // Implementação fictícia: escrever na memória
    throw std::runtime_error("writeMemory not implemented");
}

uint32_t Cpu::readMemory(uint32_t address) {
    // Implementação fictícia: ler da memória
    throw std::runtime_error("readMemory not implemented");
    return 0;
}

void Cpu::setBaseLimit(uint32_t base, uint32_t limit) {
    // Implementação fictícia: configurar base e limite
    throw std::runtime_error("setBaseLimit not implemented");
}

uint32_t Cpu::checkInterrupts() {
    // Implementação fictícia: verificar interrupções
    throw std::runtime_error("checkInterrupts not implemented");
    return 0;
}

void Cpu::executeNextInstruction() {
    // Implementação fictícia: executar instrução
    throw std::runtime_error("executeNextInstruction not implemented");
}

uint32_t Cpu::getRegister(uint32_t index) {
    // Implementação fictícia: obter registrador
    throw std::runtime_error("getRegister not implemented");
    return 0;
}

void Cpu::setRegister(uint32_t index, uint32_t value) {
    // Implementação fictícia: definir registrador
    throw std::runtime_error("setRegister not implemented");
}

void Cpu::setProgramCounter(uint32_t pc) {
    // Implementação fictícia: definir PC
    throw std::runtime_error("setProgramCounter not implemented");
}

uint32_t Cpu::getProgramCounter() {
    // Implementação fictícia: obter PC
    throw std::runtime_error("getProgramCounter not implemented");
    return 0;
}

std::vector<uint32_t> Cpu::getRegisters() {
    // Implementação fictícia: obter todos os registradores
    throw std::runtime_error("getRegisters not implemented");
    return std::vector<uint32_t>();
}

void Cpu::setRegisters(const std::vector<uint32_t>& regs) {
    // Implementação fictícia: definir todos os registradores
    throw std::runtime_error("setRegisters not implemented");
}
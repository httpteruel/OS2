#include "cpu.h" // gerenciamento de memoria
#include <stdexcept>

Cpu::Cpu() : pc(0), vmemMode(BaseLimit), vmemPaddrBase(0), vmemSize(1024) {
    for (int i = 0; i < 8; i++) gpr[i] = 0;
}

uint16_t Cpu::get_pc() { return pc; }
void Cpu::set_pc(uint16_t value) { pc = value; }
uint16_t Cpu::get_gpr(uint8_t code) { return gpr[code]; }
void Cpu::set_gpr(uint8_t code, uint16_t value) { gpr[code] = value; }
VmemMode Cpu::get_vmem_mode() { return vmemMode; }
void Cpu::set_vmem_mode(VmemMode mode) { vmemMode = mode; }
uint16_t Cpu::get_vmem_paddr_base() { return vmemPaddrBase; }
void Cpu::set_vmem_paddr_base(uint16_t value) { vmemPaddrBase = value; }
uint16_t Cpu::get_vmem_size() { return vmemSize; }
void Cpu::set_vmem_size(uint16_t value) { vmemSize = value; }

uint16_t Cpu::translateAddress(uint16_t virtAddr) {
    if (vmemMode == BaseLimit) {
        if (virtAddr >= vmemSize) {
            throw std::runtime_error("VmemPageFault: Endereço fora dos limites");
        }
        return vmemPaddrBase + virtAddr;
    }
    return virtAddr; // Disabled
}
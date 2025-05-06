#ifndef CPU_H
#define CPU_H

#include <cstdint>

enum VmemMode { Disabled, BaseLimit, Paging };

class Cpu {
private:
    uint16_t pc;              // Program Counter
    uint16_t gpr[8];          // 8 registradores de propósito geral (r0-r7)
    VmemMode vmemMode;        // Modo de memória virtual
    uint16_t vmemPaddrBase;   // Endereço físico base
    uint16_t vmemSize;        // Tamanho da memória virtual

public:
    Cpu();
    uint16_t get_pc();
    void set_pc(uint16_t value);
    uint16_t get_gpr(uint8_t code);
    void set_gpr(uint8_t code, uint16_t value);
    VmemMode get_vmem_mode();
    void set_vmem_mode(VmemMode mode);
    uint16_t get_vmem_paddr_base();
    void set_vmem_paddr_base(uint16_t value);
    uint16_t get_vmem_size();
    void set_vmem_size(uint16_t value);
    uint16_t translateAddress(uint16_t virtAddr);
};

#endif // CPU_H
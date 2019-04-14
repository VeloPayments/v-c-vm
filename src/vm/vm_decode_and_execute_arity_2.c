#include <vcvm/instruction.h>
#include <vcvm/vm.h>

int vm_decode_and_execute_arity_2(vm_t* vm, const instruction_t* instr)
{
    uint32_t i = *(vm->bytecode->instructions + vm->ip++);
    uint16_t a = (i & (uint32_t)0x00fff000) >> (uint8_t)12;
    uint16_t b = (i & (uint32_t)0x00000fff);
    return instr->handler.arity2(vm, a, b);
}
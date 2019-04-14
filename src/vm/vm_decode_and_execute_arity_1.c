#include <vcvm/instruction.h>
#include <vcvm/vm.h>
#include <vpr/parameters.h>

int vm_decode_and_execute_arity_1(vm_t* vm, const instruction_t* instr)
{
    const uint32_t i = *(vm->bytecode->instructions + vm->ip++);
    uint32_t a = (i & (uint32_t)0x00FFFFFF);
    return instr->handler.arity1(vm, a);
}
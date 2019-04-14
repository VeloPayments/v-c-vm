#include <vcvm/instruction.h>
#include <vcvm/vm.h>
#include <string.h>

int vm_decode_and_execute_arity_3(vm_t* vm, const instruction_t* instr)
{
    uint32_t i = *(vm->bytecode->instructions + vm->ip++);
    uint8_t bytes[4];

    memcpy(&bytes, &i, sizeof(uint32_t));

    return instr->handler.arity3(vm, bytes[1], bytes[2], bytes[3]);
}
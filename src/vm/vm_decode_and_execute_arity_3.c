#include <vcvm/instruction.h>
#include <vcvm/vm.h>

int vm_decode_and_execute_arity_3(vm_t* vm, const instruction_t* instr)
{
    const uint8_t* ip = vm->bytecode->instructions;
    vm->bytecode->instructions++;
    return instr->handler.arity3(vm, ip[1], ip[2], ip[3]);
}
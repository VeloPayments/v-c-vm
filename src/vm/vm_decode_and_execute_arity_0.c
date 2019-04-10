#include <vcvm/instruction.h>
#include <vcvm/vm.h>

int vm_decode_and_execute_arity_0(vm_t* vm, const instruction_t* instr)
{
    vm->bytecode->instructions++;
    return instr->handler.arity0(vm);
}
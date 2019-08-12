#include <vcvm/instruction.h>
#include <vcvm/vm.h>

int vcvm_vm_decode_and_execute_arity_0(vcvm_vm_t* vm, const vcvm_instruction_t* instr)
{
    vm->ip++;
    return instr->handler.arity0(vm);
}
#include <vcvm/instruction.h>
#include <vcvm/vm.h>

int vm_decode_and_execute_arity_1(vm_t* vm, const instruction_t* instr)
{
    /* uint32_t arg1 = (instr & 0x00FFFFFF); (edited)  */
    vm->bytecode->instructions++;
    return instr->handler.arity1(vm);
}
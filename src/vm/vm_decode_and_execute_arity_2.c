#include <vcvm/instruction.h>
#include <vcvm/vm.h>

int vm_decode_and_execute_arity_2(vm_t* vm, const instruction_t* instr)
{
    /*
top 8 bits: (i & 0xFF000000) >> 24
middle 12 bits: (i & 0x00fff000) >> 12
bottom 12 bits: (i & 0x00000fff)
     */

    vm->bytecode->instructions++;
    return instr->handler.arity0(vm);
}
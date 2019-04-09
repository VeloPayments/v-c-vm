#include <vcvm/instruction.h>
#include <vcvm/intrinsic.h>
#include <include/vcvm/vm.h>

instruction_t *vm_decode_opcode(vm_t *vm)
{
    vm->bytecode->instructions++;
    return NULL;
}

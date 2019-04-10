#include <vcvm/instruction.h>
#include <vcvm/intrinsic.h>
#include <include/vcvm/vm.h>

const instruction_t *vm_decode_opcode(vm_t *vm)
{
    uint8_t opcode = (*vm->bytecode->instructions) & 0xFF;
    vm->bytecode->instructions++;
    return opcodes[opcode];
}

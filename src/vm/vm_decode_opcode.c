#include <vcvm/instruction.h>
#include <vcvm/intrinsic.h>
#include <vcvm/vm.h>

const vcvm_instruction_t* vcvm_vm_decode_opcode(vcvm_vm_t* vm)
{
    uint32_t i = *(vm->bytecode->instructions + vm->ip);
    uint8_t opcode = (i & (uint32_t)0xFF000000) >> (uint8_t)24;
    return vcvm_instructions[opcode];
}

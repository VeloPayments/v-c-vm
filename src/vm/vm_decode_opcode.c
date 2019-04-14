#include <vcvm/instruction.h>
#include <vcvm/intrinsic.h>
#include <vcvm/vm.h>
#include <vcvm/opcodes.h>

const instruction_t* vm_decode_opcode(vm_t* vm)
{
    uint32_t i = *(vm->bytecode->instructions + vm->ip);
    uint8_t opcode = (i & (uint8_t)0xFF000000) >> (uint8_t)24;
    return opcodes[opcode];
}
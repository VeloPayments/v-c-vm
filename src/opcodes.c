#include <vcvm/opcodes.h>

uint32_t vcvm_opcode_pack_no_args(uint8_t i)
{
    return htonl(i);
}

uint32_t vcvm_opcode_pack_one_arg(uint8_t i, uint32_t x)
{
    uint32_t instr = htonl(i);
    return instr | x;
}

uint32_t vcvm_opcode_pack_two_args(uint8_t i, uint16_t x, uint16_t y)
{
    uint32_t instr = htonl(i);
    instr |= x << 12;
    instr |= y;
    return instr;
}

uint32_t vcvm_opcode_pack_three_args(uint8_t i, uint8_t x, uint8_t y, uint8_t z)
{
    uint8_t bytes[4] = { i, x, y, z };
    uint32_t packed;
    memcpy(&packed, bytes, sizeof(uint32_t));
    return htonl(packed);
}
#include <minunit/minunit.h>
#include <cstdint>
#include <cstring>
#include <netinet/in.h>
#include <vcvm/instruction.h>

TEST_SUITE(opcode);

TEST(sanity)
{
    uint32_t i = 0x0A0B0C0D;

    // Opcode mask (top 8 bits)
    uint8_t o1 = (i & (uint32_t)0xFF000000) >> (uint8_t)24;
    TEST_EXPECT(o1 == 0xA);

    // 1 arg: 24 bit.
    uint32_t o2 = (i & (uint32_t)0x00FFFFFF);
    TEST_EXPECT(o2 == 0xB0C0D);

    // 2 arg: 12 bits each
    uint16_t o3 = (i & (uint32_t)0x00fff000) >> (uint8_t)12;
    uint16_t o4 = (i & (uint32_t)0x00000fff);
    TEST_EXPECT(o3 == 0xB0);
    TEST_EXPECT(o4 == 0xC0D);

    uint8_t bytes[4];
    uint32_t i2 = htonl(i);
    memcpy(bytes, &i2, sizeof(uint32_t));
    TEST_EXPECT(bytes[0] == 0xA);
    TEST_EXPECT(bytes[1] == 0xB);
    TEST_EXPECT(bytes[2] == 0xC);
    TEST_EXPECT(bytes[3] == 0xD);
}

TEST(vcvm_halt)
{
    uint32_t i = 0xFF000000;
    uint8_t opcode = (i & (uint32_t)0xFF000000) >> (uint8_t)24;
    const vcvm_instruction_t* instr = vcvm_instructions[opcode];
    TEST_EXPECT(instr == &VCVM_HALT);
}

TEST(vcvm_nop)
{
    uint32_t i = 0x00000000;
    uint8_t opcode = (i & (uint32_t)0xFF000000) >> (uint8_t)24;
    const vcvm_instruction_t* instr = vcvm_instructions[opcode];
    TEST_EXPECT(instr == &VCVM_NOP);
}
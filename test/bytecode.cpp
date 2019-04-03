#include <minunit/minunit.h>
#include <cstdint>
#include <src/bytecode/bytecode_internal.h>
#include <vcvm/error_codes.h>

TEST_SUITE(bytecode);

const uint8_t good_magic_number_program[] = {
        // 0xDECAF
        0x0, 0x0, 0x0, 0x0, 0x0, 0xD, 0xEC, 0xAF,
};

TEST(good_magic_number_program) {
    uint32_t magic;
    int result = bytecode_read_magic(&magic, good_magic_number_program, 8);
    if (result != VCVM_STATUS_SUCCESS)
    {

    }
    TEST_SUCCESS()
}
#include <minunit/minunit.h>
#include <cstdint>
#include <vcvm/error_codes.h>
#include <vcvm/bytecode.h>
#include <string.h>
#include <vpr/allocator/malloc_allocator.h>

TEST_SUITE(bytecode);

const size_t string_const_size = 36;
const uint8_t string_const[] = {
        // 0x00DECAF
        0x0, 0xD, 0xEC, 0xAF,
        // 0 integer constants
        0x0, 0x0, 0x0, 0x0,
        // 1 string constant,
        0x0, 0x0, 0x0, 0x2,
        // length of the first constant
        0x0, 0x0, 0x0, 0x4,
        // test
        0x74, 0x65, 0x73, 0x74,
        // length of the second constant
        0x0, 0x0, 0x0, 0x4,
        // heya
        0x68, 0x65, 0x79, 0x61,
        // No artifacts
        0x0, 0x0, 0x0, 0x0,
        // No intrinsics
        0x0, 0x0, 0x0, 0x0
};

TEST(read_string_const)
{
    allocator_options_t allocator_options;
    malloc_allocator_options_init(&allocator_options);

    bytecode_t bytecode;
    int result = bytecode_init(&bytecode, &allocator_options, string_const, string_const_size);
    TEST_ASSERT(result == VCVM_STATUS_SUCCESS);

    TEST_EXPECT(bytecode.string_count == 2);
    TEST_EXPECT(strcmp(*bytecode.strings, "test") == 0);
    TEST_EXPECT(strcmp(*(bytecode.strings + 1), "heya") == 0);

    dispose((disposable_t *) &bytecode);
    dispose((disposable_t *) &allocator_options);
}
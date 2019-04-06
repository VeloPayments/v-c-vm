#include <minunit/minunit.h>
#include <cstdint>
#include <vcvm/error_codes.h>
#include <vcvm/bytecode.h>
#include <string.h>
#include <vpr/allocator/malloc_allocator.h>

TEST_SUITE(bytecode);

// ff27a555-eaa7-4529-833c-c1b8d8229c84
#define UUID_1 0xff, 0x27, 0xa5, 0x55, 0xea, 0xa7, 0x45, 0x29, 0x83, 0x3c, 0xc1, 0xb8, 0xd8, 0x22, 0x9c, 0x84
// 18af7ccd-baad-4dbb-a4a9-0171cca1e65a
#define UUID_2 0x18, 0xaf, 0x7c, 0xcd, 0xba, 0xad, 0x4d, 0xbb, 0xa4, 0xa9, 0x1, 0x71, 0xcc, 0xa1, 0xe6, 0x5a

const size_t string_const_size = 40;
const uint8_t string_const[] = {
    // 0x00DECAF
    0x0, 0xD, 0xEC, 0xAF,
    // 0 integer constants
    0x0, 0x0, 0x0, 0x0,
    // 2 string constants,
    0x0, 0x0, 0x0, 0x2,
    // length of the first constant
    0x0, 0x0, 0x0, 0x4,
    // "test"
    0x74, 0x65, 0x73, 0x74,
    // length of the second constant
    0x0, 0x0, 0x0, 0x4,
    // "heya"
    0x68, 0x65, 0x79, 0x61,
    // No artifacts
    0x0, 0x0, 0x0, 0x0,
    // No intrinsics
    0x0, 0x0, 0x0, 0x0,
    // No instructions
    0x0, 0x0, 0x0, 0x0};


const size_t integer_constant_size = 40;
const uint8_t integer_constant[] = {
    // 0x00DECAF
    0x0, 0xD, 0xEC, 0xAF,
    // 0 integer constants
    0x0, 0x0, 0x0, 0x2,
    // 10
    0x0, 0x0, 0x0, 0xA,
    // 15
    0x0, 0x0, 0x0, 0xF,
    // No string constants,
    0x0, 0x0, 0x0, 0x0,
    // No artifacts
    0x0, 0x0, 0x0, 0x0,
    // No intrinsics
    0x0, 0x0, 0x0, 0x0,
    // No instructions
    0x0, 0x0, 0x0, 0x0};


const size_t artifact_constant_size = 64;
const uint8_t artifact_constant[] = {
    // 0x00DECAF
    0x0, 0xD, 0xEC, 0xAF,
    // 0 integer constants
    0x0, 0x0, 0x0, 0x2,
    // 10
    0x0, 0x0, 0x0, 0xA,
    // 15
    0x0, 0x0, 0x0, 0xF,
    // No string constants,
    0x0, 0x0, 0x0, 0x0,
    // 2 artifacts
    0x0, 0x0, 0x0, 0x2,
    UUID_1,
    UUID_2,
    // No intrinsics
    0x0, 0x0, 0x0, 0x0,
    // No instructions
    0x0, 0x0, 0x0, 0x0};


const size_t intrinsic_constant_size = 72;
const uint8_t intrinsic_constant[] = {
    // 0x00DECAF
    0x0, 0xD, 0xEC, 0xAF,
    // 0 integer constants
    0x0, 0x0, 0x0, 0x0,
    // No string constants,
    0x0, 0x0, 0x0, 0x0,
    // no artifacts
    0x0, 0x0, 0x0, 0x0,
    // 2 intrinsics
    0x0, 0x0, 0x0, 0x2,
    // uuid 1
    UUID_1,
    // 1st one nargs
    0x0, 0x0, 0x0, 0x2,
    // 1st one nrets
    0x0, 0x0, 0x0, 0x4,
    // uuid 2
    UUID_2,
    // 1st one nargs
    0x0, 0x0, 0x0, 0x4,
    // 1st one nrets
    0x0, 0x0, 0x0, 0x8,
    // No instructions
    0x0, 0x0, 0x0, 0x0};

TEST(read_intrinsic_constant)
{
    allocator_options_t allocator_options;
    malloc_allocator_options_init(&allocator_options);

    bytecode_t bytecode;
    int result = bytecode_init(&bytecode, &allocator_options, intrinsic_constant, intrinsic_constant_size);
    TEST_ASSERT(result == VCVM_STATUS_SUCCESS);

    TEST_EXPECT(bytecode.intrinsics_count == 2);

    uint8_t uuid1[16] = {UUID_1};
    intrinsic_t* intrinsic_1 = *(bytecode.intrinsics);
    TEST_EXPECT(intrinsic_1->nargs == 0x2);
    TEST_EXPECT(intrinsic_1->nrets == 0x4);
    for (uint8_t i = 0; i < 16; ++i)
    {
        TEST_EXPECT(uuid1[i] == intrinsic_1->uuid[i]);
    }

    uint8_t uuid2[16] = {UUID_2};
    intrinsic_t* intrinsic_2 = *(bytecode.intrinsics + 1);
    TEST_EXPECT(intrinsic_2->nargs == 0x4);
    TEST_EXPECT(intrinsic_2->nrets == 0x8);
    for (uint8_t i = 0; i < 16; ++i)
    {
        TEST_EXPECT(uuid2[i] == intrinsic_2->uuid[i]);
    }

    dispose((disposable_t*)&bytecode);
    dispose((disposable_t*)&allocator_options);
}


TEST(read_artifact_const)
{
    allocator_options_t allocator_options;
    malloc_allocator_options_init(&allocator_options);

    bytecode_t bytecode;
    int result = bytecode_init(&bytecode, &allocator_options, artifact_constant, artifact_constant_size);
    TEST_ASSERT(result == VCVM_STATUS_SUCCESS);

    TEST_EXPECT(bytecode.artifact_count == 2);

    uint8_t uuid1[16] = {UUID_1};
    uint8_t* expected_uuid_1 = *(bytecode.artifacts);

    for (uint8_t i = 0; i < 16; ++i)
    {
        TEST_EXPECT(uuid1[i] == expected_uuid_1[i]);
    }

    uint8_t uuid2[16] = {UUID_2};
    uint8_t* expected_uuid_2 = *(bytecode.artifacts + 1);

    for (uint8_t i = 0; i < 16; ++i)
    {
        TEST_EXPECT(uuid2[i] == expected_uuid_2[i]);
    }

    dispose((disposable_t*)&bytecode);
    dispose((disposable_t*)&allocator_options);
}

TEST(read_integer_const)
{
    allocator_options_t allocator_options;
    malloc_allocator_options_init(&allocator_options);

    bytecode_t bytecode;
    int result = bytecode_init(&bytecode, &allocator_options, integer_constant, integer_constant_size);
    TEST_ASSERT(result == VCVM_STATUS_SUCCESS);

    TEST_EXPECT(bytecode.integer_count == 2);
    TEST_EXPECT(*(bytecode.integers) == 10);
    TEST_EXPECT(*(bytecode.integers + 1) == 15);

    dispose((disposable_t*)&bytecode);
    dispose((disposable_t*)&allocator_options);
}

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

    dispose((disposable_t*)&bytecode);
    dispose((disposable_t*)&allocator_options);
}
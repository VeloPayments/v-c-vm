#include <minunit/minunit.h>
#include <cstdint>
#include <vcvm/error_codes.h>
#include <vcvm/bytecode.h>
#include <string.h>
#include <vpr/allocator/malloc_allocator.h>
#include <vpr/parameters.h>
#include "bytecode.h"

TEST_SUITE(bytecode);

TEST(read_instructions)
{
    allocator_options_t allocator_options;
    malloc_allocator_options_init(&allocator_options);

    bytecode_t bytecode;
    int result = bytecode_init(&bytecode, &allocator_options, intruction_constant, intruction_constant_size, nullptr);
    TEST_ASSERT(result == VCVM_STATUS_SUCCESS);

    TEST_EXPECT(bytecode.instruction_count == 2);
    TEST_EXPECT(*(bytecode.instructions) == 10);
    TEST_EXPECT(*(bytecode.instructions + 1) == 15);

    dispose((disposable_t*)&bytecode);
    dispose((disposable_t*)&allocator_options);
}

static void fake_dispose(void* UNUSED(ctx))
{
}

static uint8_t uuid1[16] = {UUID_1};
static uint8_t uuid2[16] = {UUID_2};
static intrinsic_t intrinsic_1 = {
    .hdr = disposable {.dispose = &fake_dispose},
    .allocator_options = nullptr,
    .uuid = uuid1,
    .nargs = 2,
    .nrets = 4,
};
static intrinsic_t intrinsic_2 = {
    .hdr = disposable {.dispose = &fake_dispose},
    .allocator_options = nullptr,
    .uuid = uuid2,
    .nargs = 4,
    .nrets = 8,
};

static int resolve_test_intrinsics(intrinsic_t** intrinsic, uint8_t* uuid, uint32_t UNUSED(nargs), uint32_t UNUSED(nrets))
{
    if (memcmp(uuid, uuid1, 16) == 0)
    {
        *intrinsic = &intrinsic_1;
        return VCVM_STATUS_SUCCESS;
    }
    else if (memcmp(uuid, uuid2, 16) == 0)
    {
        *intrinsic = &intrinsic_2;
        return VCVM_STATUS_SUCCESS;
    }
    return VCVM_INTRINSIC_NOT_FOUND;
}

TEST(read_intrinsics)
{
    allocator_options_t allocator_options;
    malloc_allocator_options_init(&allocator_options);

    bytecode_t bytecode;
    int result = bytecode_init(&bytecode, &allocator_options, intrinsic_constant, intrinsic_constant_size, &resolve_test_intrinsics);
    TEST_ASSERT(result == VCVM_STATUS_SUCCESS);

    TEST_EXPECT(bytecode.intrinsics_count == 2);
    TEST_EXPECT(memcmp(uuid1, (*(bytecode.intrinsics))->uuid, 16) == 0);
    TEST_EXPECT(memcmp(uuid2, (*(bytecode.intrinsics + 1))->uuid, 16) == 0);

    dispose((disposable_t*)&bytecode);
    dispose((disposable_t*)&allocator_options);
}


TEST(read_artifacts)
{
    allocator_options_t allocator_options;
    malloc_allocator_options_init(&allocator_options);

    bytecode_t bytecode;
    int result = bytecode_init(&bytecode, &allocator_options, artifact_constant, artifact_constant_size, nullptr);
    TEST_ASSERT(result == VCVM_STATUS_SUCCESS);

    TEST_EXPECT(bytecode.artifact_count == 2);
    TEST_EXPECT(memcmp(uuid1, *(bytecode.artifacts), 16) == 0);
    TEST_EXPECT(memcmp(uuid2, *(bytecode.artifacts + 1), 16) == 0);

    dispose((disposable_t*)&bytecode);
    dispose((disposable_t*)&allocator_options);
}

TEST(read_integers)
{
    allocator_options_t allocator_options;
    malloc_allocator_options_init(&allocator_options);

    bytecode_t bytecode;
    int result = bytecode_init(&bytecode, &allocator_options, integer_constant, integer_constant_size, nullptr);
    TEST_ASSERT(result == VCVM_STATUS_SUCCESS);

    TEST_EXPECT(bytecode.integer_count == 2);
    TEST_EXPECT(*(bytecode.integers) == 10);
    TEST_EXPECT(*(bytecode.integers + 1) == 15);

    dispose((disposable_t*)&bytecode);
    dispose((disposable_t*)&allocator_options);
}

TEST(read_strings)
{
    allocator_options_t allocator_options;
    malloc_allocator_options_init(&allocator_options);

    bytecode_t bytecode;
    int result = bytecode_init(&bytecode, &allocator_options, string_const, string_const_size, nullptr);
    TEST_ASSERT(result == VCVM_STATUS_SUCCESS);

    TEST_EXPECT(bytecode.string_count == 2);
    TEST_EXPECT(strcmp(*bytecode.strings, "test") == 0);
    TEST_EXPECT(strcmp(*(bytecode.strings + 1), "heya") == 0);

    dispose((disposable_t*)&bytecode);
    dispose((disposable_t*)&allocator_options);
}
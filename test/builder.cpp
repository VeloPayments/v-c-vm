#include <minunit/minunit.h>
#include <vcvm/builder.h>
#include <vpr/allocator.h>
#include <vpr/disposable.h>
#include <vpr/allocator/malloc_allocator.h>
#include <vcvm/stdlib.h>

TEST_SUITE(builder);

TEST(builder_add_string)
{
    allocator_options_t allocator;
    malloc_allocator_options_init(&allocator);

    bytecode_builder_t builder;
    bytecode_builder_init(&builder, &allocator);

    int first_index = bytecode_builder_add_string(&builder, const_cast<char*>("test"));
    int same_string_index = bytecode_builder_add_string(&builder, const_cast<char*>("test"));
    int different_string_index = bytecode_builder_add_string(&builder, const_cast<char*>("testing"));

    TEST_EXPECT(first_index == same_string_index);
    TEST_EXPECT(first_index != different_string_index);

    dispose((disposable_t*)&builder);
    dispose((disposable_t*)&allocator);
}

TEST(builder_add_int)
{
    allocator_options_t allocator;
    malloc_allocator_options_init(&allocator);

    bytecode_builder_t builder;
    bytecode_builder_init(&builder, &allocator);

    int first_index = bytecode_builder_add_int(&builder, 0xCAFE);
    int same_index = bytecode_builder_add_int(&builder, 0xCAFE);
    int different_index = bytecode_builder_add_int(&builder, 0xBABE);

    TEST_EXPECT(first_index == same_index);
    TEST_EXPECT(first_index != different_index);

    dispose((disposable_t*)&builder);
    dispose((disposable_t*)&allocator);
}

TEST(builder_add_intrinsic)
{
    allocator_options_t allocator;
    malloc_allocator_options_init(&allocator);

    bytecode_builder_t builder;
    bytecode_builder_init(&builder, &allocator);

    int first_index = bytecode_builder_add_intrinsic(&builder, &STRING_CONTAINS);
    int same_index = bytecode_builder_add_intrinsic(&builder, &STRING_CONTAINS);
    int different_index = bytecode_builder_add_intrinsic(&builder, &STRING_EQUALS);

    TEST_EXPECT(first_index == same_index);
    TEST_EXPECT(first_index != different_index);

    dispose((disposable_t*)&builder);
    dispose((disposable_t*)&allocator);
}

TEST(builder_add_artifact)
{
    allocator_options_t allocator;
    malloc_allocator_options_init(&allocator);

    bytecode_builder_t builder;
    bytecode_builder_init(&builder, &allocator);

    const uint8_t uuid1[16] = {
        0xC2, 0xD1, 0x9B, 0xF0, 0x53, 0x19, 0x46, 0x3B, 0xA5, 0xD1, 0x2B, 0xD9, 0x8C, 0x9C, 0x72, 0x84
    };

    const uint8_t uuid2[16] = {
        0x90, 0xDD, 0x56, 0x83, 0x36, 0xD2, 0x47, 0x7D, 0x94, 0x8F, 0xF6, 0xDF, 0x51, 0x86, 0x71, 0x65
    };


    int first_index = bytecode_builder_add_uuid(&builder, (uint8_t *) uuid1);
    int same_index = bytecode_builder_add_uuid(&builder, (uint8_t *) uuid1);
    int different_index = bytecode_builder_add_uuid(&builder, (uint8_t *) uuid2);

    TEST_EXPECT(first_index == same_index);
    TEST_EXPECT(first_index != different_index);

    dispose((disposable_t*)&builder);
    dispose((disposable_t*)&allocator);
}

TEST(builder_add_instructions)
{
    allocator_options_t allocator;
    malloc_allocator_options_init(&allocator);

    bytecode_builder_t builder;
    bytecode_builder_init(&builder, &allocator);

    bytecode_builder_add_instruction(&builder, 0xCAFEBABE);
    bytecode_builder_add_instruction(&builder, 0xDECAFBAB);

    auto elements = (uint32_t*) builder.instructions.array;

    TEST_EXPECT(*(elements) == 0xCAFEBABE);
    TEST_EXPECT(*(elements+1) == 0xDECAFBAB);

    dispose((disposable_t*)&builder);
    dispose((disposable_t*)&allocator);
}
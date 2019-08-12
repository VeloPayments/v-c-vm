#include <minunit/minunit.h>
#include <vpr/allocator/malloc_allocator.h>
#include <vpr/parameters.h>
#include <vcvm/error_codes.h>
#include <vcvm/bytecode.h>
#include <vcvm/builder.h>
#include <vcvm/opcodes.h>
#include <vcvm/stdlib.h>

TEST_SUITE(usage);

int resolve(const vcvm_intrinsic_t** intrinsic, uint8_t* UNUSED(uuid), uint32_t UNUSED(nargs), uint32_t UNUSED(nrets))
{
    *intrinsic = &VCVM_STRING_CONTAINS;
    return 0;
}

TEST(simple_usage)
{
    allocator_options_t allocator;
    malloc_allocator_options_init(&allocator);

    vcvm_bytecode_builder_t builder;
    vcvm_bytecode_builder_init(&builder, &allocator);

    vcvm_bytecode_builder_add_instruction(&builder,
        vcvm_opcode_pack_one_arg(
            VCVM_OPCODE_LOAD_CONST_STRING,
            vcvm_bytecode_builder_add_string(&builder, const_cast<char*>("test"))));

    vcvm_bytecode_builder_add_instruction(&builder,
        vcvm_opcode_pack_one_arg(VCVM_OPCODE_LOAD_CONST_STRING,
            vcvm_bytecode_builder_add_string(&builder, const_cast<char*>("testing"))));

    vcvm_bytecode_builder_add_instruction(&builder,
        vcvm_opcode_pack_one_arg(VCVM_OPCODE_CALL_INTRINSIC,
            vcvm_bytecode_builder_add_intrinsic(&builder, &VCVM_STRING_CONTAINS)));

    size_t size = vcvm_bytecode_builder_total_size(&builder);

    auto* bytes = static_cast<uint8_t*>(allocate(&allocator, size));
    size_t written = 0;
    vcvm_bytecode_builder_emit(&builder, bytes, size, &written);

    TEST_ASSERT(written == size);

    vcvm_bytecode_t parser;
    int result = vcvm_bytecode_init(&parser, &allocator, bytes, size, &resolve);

    TEST_ASSERT(result == VCVM_STATUS_SUCCESS);

    dispose((disposable_t*)&parser);

    release(&allocator, bytes);
    dispose((disposable_t*)&builder);
    dispose((disposable_t*)&allocator);
}

#include <minunit/minunit.h>
#include <vcvm/builder.h>
#include <vcvm/opcodes.h>
#include <vpr/allocator/malloc_allocator.h>
#include <vcvm/bytecode.h>
#include <vcvm/stdlib.h>
#include <iostream>
#include <vpr/parameters.h>

TEST_SUITE(usage);

void dump(const void* mem, unsigned int n)
{
    const char* p = reinterpret_cast<const char*>(mem);
    for (unsigned int i = 0; i < n; i++)
    {
        std::cout << std::hex << int(p[i]) << " ";
    }
    std::cout << std::endl;
}

TEST(simple_build)
{
    allocator_options_t allocator;
    malloc_allocator_options_init(&allocator);

    bytecode_builder_t builder;
    bytecode_builder_init(&builder, &allocator);

    bytecode_builder_add_instruction(&builder, opcode_pack_one_arg(OPCODE_LOAD_CONST_STRING, bytecode_builder_add_string(&builder, const_cast<char*>("test"))));
    bytecode_builder_add_instruction(&builder, opcode_pack_one_arg(OPCODE_LOAD_CONST_STRING, bytecode_builder_add_string(&builder, const_cast<char*>("test"))));
    bytecode_builder_add_instruction(&builder, opcode_pack_one_arg(OPCODE_CALL_INTRINSIC, bytecode_builder_add_intrinsic(&builder, &STRING_CONTAINS)));

    size_t size = bytecode_builder_total_size(&builder);

    auto* bytes = static_cast<uint8_t*>(allocate(&allocator, size));
    bytecode_builder_emit(&builder, bytes, size);

    dump(bytes, size);

    release(&allocator, bytes);
    dispose((disposable_t*)&builder);
    dispose((disposable_t*)&allocator);
}

int resolve(const intrinsic_t** intrinsic, uint8_t* UNUSED(uuid), uint32_t UNUSED(nargs), uint32_t UNUSED(nrets))
{
    *intrinsic = &STRING_CONTAINS;
    return 0;
}

TEST(simple_parse)
{
    TEST_FAILURE();
    allocator_options_t allocator;
    malloc_allocator_options_init(&allocator);

    size_t size = 123;
    const uint8_t bytes[123] = { 0 };

    bytecode_t parser;
    bytecode_init(&parser, &allocator, bytes, size, &resolve);
}
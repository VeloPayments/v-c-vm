#include <minunit/minunit.h>
#include <vpr/allocator/malloc_allocator.h>
#include <vpr/parameters.h>
#include <vcvm/error_codes.h>
#include <vcvm/bytecode.h>
#include <vcvm/builder.h>
#include <vcvm/opcodes.h>
#include <vcvm/stdlib.h>
#include <vcvm/vm.h>
#include <string>
#include <iostream>
#include <ios>
#include <algorithm>
#include <sstream>

TEST_SUITE(usage);

std::string tohex(int x, int w = 7, bool upper = false) {
    std::stringstream stream;
    stream << std::hex << (x & 0xFF);
    std::string result(stream.str());
    if (upper) {
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    }
    int j = w - result.length();
    while (j-- > 0) { // zero padding
        result = '0' + result;
    }
    return result;
}


void print_xxd(std::string content, int w = 16, bool upper = false) {
    int len = content.size();
    int num = 0;
    std::string curline = "";
    int width = 9 + (w / 2) * 5 + 1;
    if (w != 0) {
        width += 3;
    }
    int cw = 1;
    int kk = 1;
    for (int i = 0; i < len ; i ++) {
        if ((i % w) == 0) {
            std::cout << tohex(num) << ": ";
            cw = 9;
        }
        char t = content[i];
        std::cout << tohex((int)t, 2, upper);
        cw += 2;
        curline += t;
        if ((i & 1) == kk) {
            std::cout << " ";
            cw += 1;
        }
        if ((i % w) == (w - 1)) {
            num += w;
            std::cout << "  ";
            cw += 2;
            int k = i - w + 1;
            for (int j = 0; j < w; j ++) {
                t = content[k ++];
                if ((int)t <= 32) { // non-printable characters
                    t = '.';
                }
                std::cout << t;
                cw ++;
            }
            std::cout << "\n\r";
            curline = "";
            cw = 0;
            if ((w & 1) == 1) {
                kk = kk == 1 ? 0 : 1;
            }
        }
    }
    // remaining characters;
    int j = width - cw + 1;
    while (j-- > 0) {
        std::cout << " ";
    }
    for (size_t i = 0; i < curline.size(); i ++) {
        char t = content[i ++];
        if ((int)t < 32) { // non-printable characters
            t = '.';
        }
        std::cout << t;
    }
}

int resolve(const intrinsic_t** intrinsic, uint8_t* UNUSED(uuid), uint32_t UNUSED(nargs), uint32_t UNUSED(nrets))
{
    *intrinsic = &STRING_CONTAINS;
    return 0;
}

TEST(simple_usage)
{
    allocator_options_t allocator;
    malloc_allocator_options_init(&allocator);

    bytecode_builder_t builder;
    bytecode_builder_init(&builder, &allocator);

    bytecode_builder_add_instruction(&builder,
        opcode_pack_one_arg(
            OPCODE_LOAD_CONST_STRING,
            bytecode_builder_add_string(&builder, const_cast<char*>("test"))));

    bytecode_builder_add_instruction(&builder,
        opcode_pack_one_arg(OPCODE_LOAD_CONST_STRING,
            bytecode_builder_add_string(&builder, const_cast<char*>("testing"))));

    bytecode_builder_add_instruction(&builder,
        opcode_pack_one_arg(OPCODE_CALL_INTRINSIC,
            bytecode_builder_add_intrinsic(&builder, &STRING_CONTAINS)));

    size_t size = bytecode_builder_total_size(&builder);

    auto* bytes = static_cast<uint8_t*>(allocate(&allocator, size));
    size_t written = 0;
    bytecode_builder_emit(&builder, bytes, size, &written);

    std::string byteview;
    byteview.assign(bytes, bytes + size);

    print_xxd(byteview);
    std::cout << "\n";

    TEST_ASSERT(written == size);

    bytecode_t parser;
    int result = bytecode_init(&parser, &allocator, bytes, size, &resolve);

    vm_t vm;
    vm_init(&vm, &allocator, nullptr, nullptr, &parser);

    vm_step(&vm);
    vm_step(&vm);
    vm_step(&vm);

    stack_value_t* value;
    vm_pop(&vm, &value);

    TEST_EXPECT(value->integer == 1);

    release(&allocator, value);

    TEST_ASSERT(result == VCVM_STATUS_SUCCESS);

    dispose((disposable_t*)&parser);

    release(&allocator, bytes);
    dispose((disposable_t*)&builder);
    dispose((disposable_t*)&allocator);
}
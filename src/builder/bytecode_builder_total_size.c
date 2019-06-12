#include <vpr/parameters.h>
#include <vcvm/builder.h>
#include <vpr/allocator.h>
#include <vcvm/size.h>

size_t bytecode_builder_total_size(bytecode_builder_t* builder)
{
    size_t total = sizeof(uint32_t); // For the magic number
    total += sizeof(uint32_t) + UUID_SIZE * builder->uuid_count;
    total += sizeof(uint32_t) + sizeof(int32_t) * builder->integer_count;
    total += sizeof(uint32_t) + INTRINSIC_SIZE * builder->intrinsic_count;
    total += sizeof(uint32_t) + (sizeof(uint32_t) * builder->string_count) + builder->string_size;
    total += sizeof(uint32_t) + sizeof(uint32_t) * builder->instruction_count;
    total += sizeof(uint32_t) + sizeof(uint32_t) * builder->jmp_count;
    return total;
}
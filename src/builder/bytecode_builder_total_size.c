#include <vpr/parameters.h>
#include <vcvm/builder.h>
#include <vpr/allocator.h>
#include <vcvm/size.h>

size_t bytecode_builder_total_size(bytecode_builder_t* builder)
{
    size_t total = sizeof(uint32_t) * builder->instructions.elements;
    total += UUID_SIZE * builder->artifact_count;
    total += sizeof(int32_t) * builder->integer_count;
    total += INTRINSIC_SIZE * builder->intrinsic_count;
    total += builder->string_size;
    total += sizeof(uint32_t);
    return total;
}
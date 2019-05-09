#include <vcvm/builder.h>
#include <string.h>
#include <vcvm/error_codes.h>

int bytecode_builder_write_instructions(bytecode_builder_t* builder, uint8_t* byte, size_t* offset)
{
    memcpy(byte + *offset, &builder->instruction_count, sizeof(uint32_t));
    *offset += sizeof(uint32_t);

    // dynamic_array::array is contiguous.
    size_t total = sizeof(uint32_t) * builder->instruction_count;
    memcpy(byte + *offset, builder->instructions.array, total);
    *offset += total;

    return VCVM_STATUS_SUCCESS;
}
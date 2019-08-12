#include <vcvm/builder.h>
#include <vpr/allocator.h>
#include <vcvm/error_codes.h>
#include <string.h>
#include "builder_internal.h"

int vcvm_bytecode_builder_emit(vcvm_bytecode_builder_t* builder, uint8_t* bytes, size_t size, size_t* written)
{
    size_t actual_size = vcvm_bytecode_builder_total_size(builder);
    if (actual_size != size)
    {
        return VCVM_ERROR_BUILDER_BAD_TOTAL_SIZE;
    }

    size_t offset = 0;
    uint32_t magic_number = 0x000DECAF;

    // Write the magic number.
    memcpy(bytes + offset, &magic_number, sizeof(uint32_t));
    offset += sizeof(uint32_t);

    int result = vcvm_bytecode_builder_write_integer_constants(builder, bytes, &offset);
    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    result = vcvm_bytecode_builder_write_string_constants(builder, bytes, &offset);
    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    result = vcvm_bytecode_builder_write_uuid_constants(builder, bytes, &offset);
    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    result = vcvm_bytecode_builder_write_intrinsic_constants(builder, bytes, &offset);
    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    result = vcvm_bytecode_builder_write_instructions(builder, bytes, &offset);
    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    result = vcvm_bytecode_builder_write_jmptable(builder, bytes, &offset);
    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    *written = offset;

done:
    return result;
}
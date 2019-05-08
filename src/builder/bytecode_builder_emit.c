#include <vpr/parameters.h>
#include <vcvm/builder.h>
#include <vpr/allocator.h>
#include <vcvm/error_codes.h>
#include <string.h>
#include "builder_internal.h"

int bytecode_builder_emit(bytecode_builder_t* builder, uint8_t* byte, size_t size)
{
    size_t actual_size = bytecode_builder_total_size(builder);
    if (actual_size != size)
    {
        return VCVM_ERROR_BUILDER_BAD_TOTAL_SIZE;
    }

    size_t offset = 0;
    uint32_t magic_number = 0xDECAF;

    // Write the magic number.
    memcpy(byte + offset, &magic_number, sizeof(uint32_t));
    offset += sizeof(uint32_t);

    int result = bytecode_builder_write_integer_constants(builder, byte, &offset, size);
    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    result = bytecode_builder_write_string_constants(builder, byte, &offset, size);
    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    result = bytecode_builder_write_artifact_constants(builder, byte, &offset, size);
    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    result = bytecode_builder_write_intrinsic_constants(builder, byte, &offset, size);
    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    result = bytecode_builder_write_instructions(builder, byte, &offset, size);
    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

done:
    return result;
}
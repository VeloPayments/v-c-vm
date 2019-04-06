#include <vcvm/bytecode.h>
#include <vcvm/error_codes.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "bytecode_internal.h"

int bytecode_read_intrinsic_constants(bytecode_t* bytecode, const uint8_t* raw, size_t size, size_t* offset)
{
    int result;
    result = bytecode_read_uint32(&bytecode->intrinsics_count, raw, size, offset);
    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    bytecode->intrinsics = (intrinsic_t**)allocate(
        bytecode->allocator_options,
        sizeof(intrinsic_t*) * bytecode->intrinsics_count);

    if (bytecode->strings == NULL)
    {
        result = VCVM_CANT_ALLOCATE;
        goto done;
    }

    memset(bytecode->intrinsics, 0, sizeof(intrinsic_t*) * bytecode->intrinsics_count);

    for (uint32_t i = 0; i < bytecode->intrinsics_count; i++)
    {
        uint32_t string_size;
        result = bytecode_read_uint32(&string_size, raw, size, offset);
        if (result != VCVM_STATUS_SUCCESS)
        {
            goto done;
        }

        char* string = (char*)allocate(bytecode->allocator_options, sizeof(char) * string_size);
        if (string == NULL)
        {
            result = VCVM_CANT_ALLOCATE;
            goto done;
        }

        result = bytecode_read_string(string, string_size, raw, size, offset);
        if (result != VCVM_STATUS_SUCCESS)
        {
            goto done;
        }

        *(bytecode->strings + i) = string;
    }

done:
    return result;
}
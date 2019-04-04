#include <vcvm/bytecode.h>
#include <vcvm/error_codes.h>
#include <string.h>
#include "bytecode_internal.h"

int bytecode_read_integer_constants(bytecode_t* bytecode, const uint8_t* raw, size_t size, size_t* offset)
{
    int result;
    result = bytecode_read_uint32(&bytecode->integer_count, raw, size, offset);
    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    // Read out the integer constants.
    bytecode->integers = (uint32_t*)allocate(
        bytecode->allocator_options,
        sizeof(uint32_t) * bytecode->integer_count);

    if (bytecode->integers == NULL)
    {
        result = VCVM_CANT_ALLOCATE;
        goto done;
    }

    // Ensure the space is entirely blanked out
    memset(bytecode->integers, 0, sizeof(uint32_t) * bytecode->integer_count);

    for (uint32_t i = 0; i < bytecode->integer_count; i++)
    {
        uint32_t value;
        result = bytecode_read_uint32(&value, raw, size, offset);
        if (result != VCVM_STATUS_SUCCESS)
        {
            goto free_integers;
        }
        *(bytecode->integers + i) = value;
    }
    goto done;

free_integers:

done:
    return result;
}
#include <vcvm/error_codes.h>
#include <vcvm/bytecode.h>
#include <string.h>
#include "bytecode_internal.h"

int bytecode_read_string_constants(bytecode_t* bytecode, const uint8_t* raw, size_t size, size_t* offset)
{
    int result;
    result = bytecode_read_uint32(&bytecode->string_count, raw, size, offset);
    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    // Read out the string constants.
    bytecode->strings = (char**)allocate(
        bytecode->allocator_options,
        sizeof(char*) * bytecode->string_count);

    if (bytecode->strings == NULL)
    {
        result = VCVM_CANT_ALLOCATE;
        goto done;
    }

    memset(bytecode->strings, 0, sizeof(char*) * bytecode->string_count);

    for (uint32_t i = 0; i < bytecode->string_count; i++)
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
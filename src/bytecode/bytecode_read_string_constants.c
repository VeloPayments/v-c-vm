#include <vcvm/error_codes.h>
#include <vcvm/bytecode.h>
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
    // Read out the integer constants.
    bytecode->strings = (char**)allocate(
        bytecode->allocator_options,
        sizeof(char*) * bytecode->string_count);

    for (uint32_t i = 0; i < bytecode->string_count; i++)
    {
        uint32_t string_size;
        result = bytecode_read_uint32(&string_size, raw, size, offset);
        if (result != VCVM_STATUS_SUCCESS)
        {
            goto free_strings;
        }

        char* string = (char*)allocate(bytecode->allocator_options, sizeof(char) * string_size);
        result = bytecode_read_string(string, string_size, raw, size, offset);
        if (result != VCVM_STATUS_SUCCESS)
        {
            goto free_strings;
        }

        *(bytecode->strings + i) = string;
    }
    goto done;

free_strings:
    for (uint32_t i = 0; i < bytecode->string_count; i++)
    {
        if ((bytecode->strings + i) != NULL)
        {
            release(bytecode->allocator_options, bytecode->strings + i);
        }
    }
done:
    return result;
}
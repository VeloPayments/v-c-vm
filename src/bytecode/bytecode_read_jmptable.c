#include <vcvm/bytecode.h>
#include <vcvm/error_codes.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "bytecode_internal.h"

int bytecode_read_jmptable(bytecode_t* bytecode, const uint8_t* raw, size_t size, size_t* offset)
{
    int result;
    result = bytecode_read_uint32(&bytecode->jmp_count, raw, size, offset);
    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    // Read out the integer constants.
    bytecode->jmp_table = (uint32_t*)allocate(
        bytecode->allocator_options,
        sizeof(uint32_t) * bytecode->jmp_count);

    if (bytecode->jmp_table == NULL)
    {
        result = VCVM_ERROR_CANT_ALLOCATE;
        goto done;
    }

    // Ensure the space is entirely blanked out
    memset(bytecode->jmp_table, 0, sizeof(int32_t) * bytecode->jmp_count);

    for (uint32_t i = 0; i < bytecode->integer_count; i++)
    {
        int32_t value;
        result = bytecode_read_int32(&value, raw, size, offset);
        if (result != VCVM_STATUS_SUCCESS)
        {
            goto done;
        }
        *(bytecode->jmp_table + i) = value;
    }

done:
    return result;
}
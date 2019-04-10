#include <vcvm/bytecode.h>
#include <vcvm/error_codes.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include "bytecode_internal.h"

int bytecode_read_instructions(bytecode_t* bytecode, const uint8_t* raw, size_t size, size_t* offset)
{
    int result = bytecode_read_uint32(&bytecode->instruction_count, raw, size, offset);
    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    bytecode->instructions = (uint8_t *)allocate(
        bytecode->allocator_options,
        sizeof(uint8_t) * bytecode->instruction_count);

    if (bytecode->instructions == NULL)
    {
        result = VCVM_CANT_ALLOCATE;
        goto done;
    }

    memset(bytecode->instructions, 0, sizeof(uint8_t) * bytecode->instruction_count);

    for (uint8_t i = 0; i < bytecode->instruction_count; i++)
    {
        uint8_t value;
        result = bytecode_read_uint8(&value, raw, size, offset);
        if (result != VCVM_STATUS_SUCCESS)
        {
            goto done;
        }
        *(bytecode->instructions + i) = value;
    }

done:
    return result;
}
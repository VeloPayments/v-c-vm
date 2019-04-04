#include <stdint.h>
#include <stddef.h>
#include <vcvm/error_codes.h>
#include <vpr/parameters.h>
#include "bytecode_internal.h"
#include <string.h>

int bytecode_read_string(char* str, size_t string_size, const uint8_t* raw, size_t size, size_t* offset)
{
    if (*offset + string_size > size)
    {
        return VCVM_BYTECODE_NOT_ENOUGH_BYTES;
    }
    memcpy(str, raw + *offset, string_size);
    *offset += string_size;
    return VCVM_STATUS_SUCCESS;
}
#include <vcvm/intrinsic.h>
#include <vcvm/error_codes.h>
#include <stddef.h>
#include <stdint.h>
#include "bytecode_internal.h"

#define INTRINSIC_SIZE (UUID_SIZE + sizeof(uint32_t) + sizeof(uint32_t))

int bytecode_read_intrinsic(intrinsic_t* intrinsic, const uint8_t* raw, size_t size, size_t* offset)
{
    if (*offset + INTRINSIC_SIZE > size)
    {
        return VCVM_BYTECODE_NOT_ENOUGH_BYTES;
    }

    int result = bytecode_read_uuid(intrinsic->uuid, raw, size, offset);
    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    result = bytecode_read_uint32(&intrinsic->nargs, raw, size, offset);
    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    result = bytecode_read_uint32(&intrinsic->nrets, raw, size, offset);
    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

done:
    return result;
}
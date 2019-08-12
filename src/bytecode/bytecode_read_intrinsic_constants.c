#include <vcvm/bytecode.h>
#include <vcvm/size.h>
#include <vcvm/error_codes.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "bytecode_internal.h"


int bytecode_read_intrinsic_constants(vcvm_bytecode_t* bytecode, const uint8_t* raw, size_t size, size_t* offset, vcvm_resolve_intrinsic_delegate_t resolve)
{
    int result = bytecode_read_uint32(&bytecode->intrinsics_count, raw, size, offset);
    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    bytecode->intrinsics = (const vcvm_intrinsic_t**)allocate(
        bytecode->allocator_options,

        sizeof(vcvm_intrinsic_t*) * bytecode->intrinsics_count);

    if (bytecode->intrinsics == NULL)
    {
        result = VCVM_ERROR_CANT_ALLOCATE;
        goto done;
    }

    memset(bytecode->intrinsics, 0, sizeof(vcvm_intrinsic_t*) * bytecode->intrinsics_count);

    for (uint32_t i = 0; i < bytecode->intrinsics_count; i++)
    {
        if (*offset + INTRINSIC_SIZE > size)
        {
            return VCVM_ERROR_BYTECODE_NOT_ENOUGH_BYTES;
        }

        uint8_t uuid[16];

        result = bytecode_read_uuid(uuid, raw, size, offset);
        if (result != VCVM_STATUS_SUCCESS)
        {
            goto done;
        }

        uint32_t nargs;
        result = bytecode_read_uint32(&nargs, raw, size, offset);
        if (result != VCVM_STATUS_SUCCESS)
        {
            goto done;
        }

        uint32_t nrets;
        result = bytecode_read_uint32(&nrets, raw, size, offset);
        if (result != VCVM_STATUS_SUCCESS)
        {
            goto done;
        }

        const vcvm_intrinsic_t* intrinsic = NULL;
        result = resolve(&intrinsic, uuid, nargs, nrets);
        if (result != VCVM_STATUS_SUCCESS)
        {
            goto done;
        }

        memset(uuid, 0, UUID_SIZE);
        *(bytecode->intrinsics + i) = intrinsic;
    }

done:
    return result;
}
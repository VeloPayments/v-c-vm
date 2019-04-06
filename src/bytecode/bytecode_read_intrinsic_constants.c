#include <vcvm/bytecode.h>
#include <vcvm/error_codes.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "bytecode_internal.h"

#define INTRINSIC_SIZE (UUID_SIZE + sizeof(uint32_t) + sizeof(uint32_t))

int bytecode_read_intrinsic_constants(bytecode_t* bytecode, const uint8_t* raw, size_t size, size_t* offset)
{
    int result = bytecode_read_uint32(&bytecode->intrinsics_count, raw, size, offset);
    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    bytecode->intrinsics = (intrinsic_t**)allocate(
        bytecode->allocator_options,
        sizeof(intrinsic_t*) * bytecode->intrinsics_count);

    if (bytecode->intrinsics == NULL)
    {
        result = VCVM_CANT_ALLOCATE;
        goto done;
    }

    memset(bytecode->intrinsics, 0, sizeof(intrinsic_t*) * bytecode->intrinsics_count);

    for (uint32_t i = 0; i < bytecode->intrinsics_count; i++)
    {
        if (*offset + INTRINSIC_SIZE > size)
        {
            return VCVM_BYTECODE_NOT_ENOUGH_BYTES;
        }

        uint8_t* uuid = (uint8_t*)allocate(bytecode->allocator_options, UUID_SIZE);
        if (uuid == NULL)
        {
            result = VCVM_CANT_ALLOCATE;
            goto done;
        }

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

        intrinsic_t* intrinsic = (intrinsic_t*)allocate(bytecode->allocator_options, sizeof(intrinsic_t));
        if (intrinsic == NULL)
        {
            result = VCVM_CANT_ALLOCATE;
            goto done;
        }

        result = intrinsic_init(intrinsic, bytecode->allocator_options, uuid, nargs, nrets);
        if (result != VCVM_STATUS_SUCCESS)
        {
            release(bytecode->allocator_options, uuid);
            goto done;
        }

        *(bytecode->intrinsics + i) = intrinsic;
    }

done:
    return result;
}
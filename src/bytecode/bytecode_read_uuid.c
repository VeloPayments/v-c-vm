#include <stdint.h>
#include <stddef.h>
#include <vcvm/error_codes.h>
#include <vcvm/size.h>
#include <string.h>


int bytecode_read_uuid(uint8_t* uuid, const uint8_t* raw, size_t size, size_t* offset)
{
    if (*offset + UUID_SIZE > size)
    {
        return VCVM_ERROR_BYTECODE_NOT_ENOUGH_BYTES;
    }
    memcpy(uuid, raw + *offset, UUID_SIZE);
    *offset += UUID_SIZE;
    return VCVM_STATUS_SUCCESS;
}
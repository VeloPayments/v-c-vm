#include <stddef.h>
#include <stdint.h>
#include <vcvm/error_codes.h>
#include <string.h>
#include <netinet/in.h>

int bytecode_read_int32(int32_t* out, const uint8_t* raw, size_t size, size_t* offset)
{
    if (*offset + sizeof(int32_t) > size)
    {
        return VCVM_ERROR_BYTECODE_NOT_ENOUGH_BYTES;
    }
    int32_t number;
    memcpy(&number, raw + *offset, sizeof(int32_t));
    *offset += sizeof(int32_t);
    *out = ntohl(number);
    return VCVM_STATUS_SUCCESS;
}
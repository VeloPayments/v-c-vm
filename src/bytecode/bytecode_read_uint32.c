#include <stddef.h>
#include <stdint.h>
#include <vcvm/error_codes.h>
#include <string.h>
#include <netinet/in.h>

int bytecode_read_uint32(uint32_t* out, const uint8_t* raw, size_t size, size_t* offset)
{
    if (*offset + sizeof(uint32_t) > size)
    {
        return VCVM_BYTECODE_NOT_ENOUGH_BYTES;
    }
    uint32_t number;
    memcpy(&number, raw + *offset, sizeof(uint32_t));
    *offset += sizeof(uint32_t);
    *out = ntohl(number);
    return VCVM_STATUS_SUCCESS;
}
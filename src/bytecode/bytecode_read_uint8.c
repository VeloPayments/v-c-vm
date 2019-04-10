#include <stddef.h>
#include <stdint.h>
#include <vcvm/error_codes.h>
#include <string.h>
#include <netinet/in.h>

int bytecode_read_uint8(uint8_t* out, const uint8_t* raw, size_t size, size_t* offset)
{
    if (*offset + sizeof(uint8_t) > size)
    {
        return VCVM_BYTECODE_NOT_ENOUGH_BYTES;
    }
    memcpy(out, raw + *offset, sizeof(uint8_t));
    *offset += sizeof(uint8_t);
    return VCVM_STATUS_SUCCESS;
}
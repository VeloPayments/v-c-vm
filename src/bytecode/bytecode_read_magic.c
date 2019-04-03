#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <netinet/in.h>
#include <vcvm/error_codes.h>

int bytecode_read_magic(uint32_t *magic_number, const uint8_t *raw, size_t length)
{
    if (length < sizeof(uint32_t))
    {
        return VCVM_BYTECODE_NOT_ENOUGH_BYTES;
    }
    memcpy(magic_number, raw, sizeof(uint32_t));
    *magic_number = ntohl(*magic_number);
    return VCVM_STATUS_SUCCESS;
}
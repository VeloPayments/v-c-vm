#include <vcvm/bytecode.h>
#include <vpr/parameters.h>
#include <vcvm/error_codes.h>

#include "bytecode_internal.h"

static void bytecode_dispose(void *ctx);

int bytecode_init(bytecode_t *bytecode, allocator_options_t *allocator_options, const uint8_t *raw, size_t size)
{
    bytecode->hdr.dispose = &bytecode_dispose;
    bytecode->allocator_options = allocator_options;

    int result = bytecode_read_magic(&bytecode->magic, raw, size);
    if (result != VCVM_STATUS_SUCCESS)
    {
        return result;
    }

    return VCVM_STATUS_SUCCESS;
}

void bytecode_dispose(void *ctx)
{
    bytecode_t *UNUSED(bytecode) = (bytecode_t *) ctx;
}
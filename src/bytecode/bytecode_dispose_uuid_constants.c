#include <vcvm/bytecode.h>
#include <stddef.h>
#include <stdint.h>

void bytecode_dispose_uuid_constants(vcvm_bytecode_t* bytecode)
{
    for (uint32_t i = 0; i < bytecode->uuid_count; i++)
    {
        if ((bytecode->uuids + i) != NULL)
        {
            release(bytecode->allocator_options, *(bytecode->uuids + i));
        }
    }
    release(bytecode->allocator_options, bytecode->uuids);
}
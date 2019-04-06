#include <vcvm/bytecode.h>
#include <stddef.h>
#include <stdint.h>

void bytecode_dispose_artifact_constants(bytecode_t* bytecode)
{
    for (uint32_t i = 0; i < bytecode->artifact_count; i++)
    {
        if ((bytecode->artifacts + i) != NULL)
        {
            release(bytecode->allocator_options, *(bytecode->artifacts + i));
        }
    }
    release(bytecode->allocator_options, bytecode->artifacts);
}
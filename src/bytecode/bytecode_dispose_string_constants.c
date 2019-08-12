#include <vcvm/bytecode.h>
#include <stddef.h>
#include <stdint.h>

void bytecode_dispose_string_constants(vcvm_bytecode_t* bytecode)
{
    for (uint32_t i = 0; i < bytecode->string_count; i++)
    {
        if ((bytecode->strings + i) != NULL)
        {
            release(bytecode->allocator_options, *(bytecode->strings + i));
        }
    }
    release(bytecode->allocator_options, bytecode->strings);
}
#include <vcvm/bytecode.h>
#include <stddef.h>
#include <stdint.h>

void bytecode_dispose_integer_constants(bytecode_t* bytecode)
{
    for (uint32_t i = 0; i < bytecode->integer_count; i++)
    {
        if ((bytecode->integers + i) != NULL)
        {
            release(bytecode->allocator_options, bytecode->integers + i);
        }
    }
    release(bytecode->allocator_options, bytecode->integers);
}

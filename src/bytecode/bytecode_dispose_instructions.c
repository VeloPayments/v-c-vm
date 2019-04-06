#include <vcvm/bytecode.h>
#include <stddef.h>
#include <stdint.h>

void bytecode_dispose_instructions(bytecode_t* bytecode)
{
    for (uint32_t i = 0; i < bytecode->instruction_count; i++)
    {
        if ((bytecode->instructions + i) != NULL)
        {
            release(bytecode->allocator_options, bytecode->instructions + i);
        }
    }
    release(bytecode->allocator_options, bytecode->instructions);
}

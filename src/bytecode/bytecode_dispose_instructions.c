#include <vcvm/bytecode.h>
#include <stddef.h>
#include <stdint.h>

void bytecode_dispose_instructions(bytecode_t* bytecode)
{
    if (bytecode->instructions != NULL)
    {
        release(bytecode->allocator_options, bytecode->instructions);
    }
}

#include <vcvm/bytecode.h>
#include <stddef.h>

void bytecode_dispose_instructions(vcvm_bytecode_t* bytecode)
{
    if (bytecode->instructions != NULL)
    {
        release(bytecode->allocator_options, bytecode->instructions);
    }
}

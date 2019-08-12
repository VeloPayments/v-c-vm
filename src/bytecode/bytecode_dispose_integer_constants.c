#include <vcvm/bytecode.h>
#include <stddef.h>

void bytecode_dispose_integer_constants(vcvm_bytecode_t* bytecode)
{
    if (bytecode->integers != NULL)
    {
        release(bytecode->allocator_options, bytecode->integers);
    }
}

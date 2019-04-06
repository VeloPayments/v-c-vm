#include <vcvm/bytecode.h>
#include <stddef.h>
#include <stdint.h>

void bytecode_dispose_integer_constants(bytecode_t* bytecode)
{
    if (bytecode->integers != NULL)
    {
        release(bytecode->allocator_options, bytecode->integers);
    }
}

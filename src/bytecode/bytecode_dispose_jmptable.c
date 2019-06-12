#include <vcvm/bytecode.h>
#include <stddef.h>
#include <stdint.h>

void bytecode_dispose_jmptable(bytecode_t* bytecode)
{
    if (bytecode->jmp_table != NULL)
    {
        release(bytecode->allocator_options, bytecode->jmp_table);
    }
}

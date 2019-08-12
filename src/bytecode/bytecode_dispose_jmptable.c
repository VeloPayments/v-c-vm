#include <vcvm/bytecode.h>
#include <stddef.h>

void bytecode_dispose_jmptable(vcvm_bytecode_t* bytecode)
{
    if (bytecode->jmp_table != NULL)
    {
        release(bytecode->allocator_options, bytecode->jmp_table);
    }
}

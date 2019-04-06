#include <vcvm/bytecode.h>
#include <stddef.h>
#include <stdint.h>

void bytecode_dispose_intrinsic_constants(bytecode_t* bytecode)
{
    for (uint32_t i = 0; i < bytecode->intrinsics_count; i++)
    {
        if ((bytecode->intrinsics + i) != NULL)
        {
            dispose((disposable_t*) bytecode->intrinsics + i);
        }
    }
    release(bytecode->allocator_options, bytecode->intrinsics);
}
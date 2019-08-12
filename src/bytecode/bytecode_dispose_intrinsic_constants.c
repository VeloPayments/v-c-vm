#include <vcvm/bytecode.h>
#include <stddef.h>
#include <stdint.h>

void bytecode_dispose_intrinsic_constants(vcvm_bytecode_t* bytecode)
{
    // Release the pointer to the pointers but don't release the pointers themselves.
    // We don't own them and they are just on loan.
    release(bytecode->allocator_options, bytecode->intrinsics);
}
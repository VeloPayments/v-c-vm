#include <vcvm/instruction.h>
#include <vcvm/error_codes.h>
#include <vpr/parameters.h>

int vcvm_nop(vcvm_vm_t* UNUSED(vm))
{
    // Guess what this does!
    return VCVM_STATUS_SUCCESS;
    // Nothing!
}

const vcvm_instruction_t VCVM_NOP = {
    .name = "NOP",
    .arity = 0,
    .handler = {
        .arity0 = &vcvm_nop,
    }
};
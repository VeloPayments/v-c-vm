#include <vcvm/instruction.h>
#include <vcvm/error_codes.h>
#include <vpr/parameters.h>

int invalid(vm_t* UNUSED(vm))
{
    return VCVM_ERROR_VM_INVALID_OPCODE;
}

const instruction_t INVALID = {
    .name = "INVALID",
    .arity = 0,
    .handler = {
        .arity0 = &invalid,
    }
};
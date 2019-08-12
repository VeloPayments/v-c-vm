#include <vcvm/instruction.h>
#include <vcvm/error_codes.h>
#include <vpr/parameters.h>

int vcvm_invalid(vcvm_vm_t* UNUSED(vm))
{
    return VCVM_ERROR_VM_INVALID_OPCODE;
}

const vcvm_instruction_t VCVM_INVALID = {
    .name = "INVALID",
    .arity = 0,
    .handler = {
        .arity0 = &vcvm_invalid,
    }
};
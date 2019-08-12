#include <vcvm/instruction.h>
#include <vcvm/error_codes.h>
#include <vpr/parameters.h>

int vcvm_halt(vcvm_vm_t* UNUSED(vm))
{
    return VCVM_ERROR_VM_HALT;
}

const vcvm_instruction_t VCVM_HALT = {
    .name = "HALT",
    .arity = 0,
    .handler = {
        .arity0 = &vcvm_halt,
    }
};
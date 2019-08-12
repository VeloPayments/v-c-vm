#include <vcvm/instruction.h>
#include <vcvm/error_codes.h>
#include <vpr/parameters.h>

int ret(vcvm_vm_t* UNUSED(vm))
{
    return VCVM_ERROR_VM_HALT;
}

const vcvm_instruction_t VCVM_RET = {
    .name = "RET",
    .arity = 0,
    .handler = {
        .arity0 = &ret,
    }
};
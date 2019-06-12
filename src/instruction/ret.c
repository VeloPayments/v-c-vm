#include <vcvm/instruction.h>
#include <vcvm/error_codes.h>
#include <vpr/parameters.h>

int ret(vm_t* UNUSED(vm))
{
    return VCVM_ERROR_VM_HALT;
}

const instruction_t RET = {
        .name = "RET",
        .arity = 0,
        .handler = {
                .arity0 = &ret,
        }
};
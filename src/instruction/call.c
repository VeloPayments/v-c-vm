#include <vcvm/instruction.h>
#include <vcvm/error_codes.h>
#include <vpr/parameters.h>

int call(vm_t* UNUSED(vm))
{
    return VCVM_ERROR_VM_HALT;
}

const instruction_t CALL = {
        .name = "CALL",
        .arity = 0,
        .handler = {
                .arity0 = &call,
        }
};
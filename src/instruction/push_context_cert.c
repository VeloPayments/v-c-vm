#include <vpr/disposable.h>
#include <vcvm/instruction.h>
#include <vcvm/error_codes.h>
#include <vpr/parameters.h>

int push_context_cert(vm_t* UNUSED(vm))
{

    return VCVM_STATUS_SUCCESS;
}

const instruction_t PUSH_CONTEXT_CERT = {
    .name = "PUSH_CONTEXT_CERT",
    .arity = 0,
    .handler = {
        .arity0 = &push_context_cert,
    }
};
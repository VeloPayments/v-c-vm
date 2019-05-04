#include <vcvm/instruction.h>
#include <vcvm/error_codes.h>
#include <vcvm/vm.h>
#include <vpr/parameters.h>

int pop(vm_t* vm)
{
    stack_value_t* value;
    int result = vm_pop(vm, &value);
    if (result != VCVM_STATUS_SUCCESS)
    {
        goto skip_dispose;
    }
    dispose((disposable_t*)value);
skip_dispose:
    return result;
}

const instruction_t POP = {
    .name = "POP",
    .arity = 0,
    .handler = {
        .arity0 = &pop,
    }
};
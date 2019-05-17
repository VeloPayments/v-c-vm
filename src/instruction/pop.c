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
        return result;
    }
    dispose((disposable_t*)value);
    release(value->allocator_options, value);
    return VCVM_STATUS_SUCCESS;
}

const instruction_t POP = {
    .name = "POP",
    .arity = 0,
    .handler = {
        .arity0 = &pop,
    }
};
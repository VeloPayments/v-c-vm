#include <vcvm/instruction.h>
#include <vcvm/error_codes.h>
#include <vcvm/vm.h>
#include <vcvm/stack_value.h>
#include <vpr/parameters.h>

int swap(vm_t* vm)
{
    int result;
    stack_value_t* top;
    stack_value_t* second;

    result = vm_pop(vm, &top);
    if (result != VCVM_STATUS_SUCCESS)
    {
        return result;
    }

    result = vm_pop(vm, &second);
    if (result != VCVM_STATUS_SUCCESS)
    {
        return result;
    }

    result = vm_push(vm, top);
    if (result != VCVM_STATUS_SUCCESS)
    {
        return result;
    }

    return vm_push(vm, second);
}

const instruction_t SWAP = {
    .name = "SWAP",
    .arity = 0,
    .handler = {
        .arity0 = &swap,
    }
};

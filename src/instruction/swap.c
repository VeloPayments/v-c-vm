#include <vcvm/instruction.h>
#include <vcvm/error_codes.h>
#include <vcvm/vm.h>
#include <vcvm/stack_value.h>
#include <vpr/parameters.h>

int vcvm_swap(vcvm_vm_t* vm)
{
    int result;
    vcvm_stack_value_t* top;
    vcvm_stack_value_t* second;

    result = vcvm_vm_pop(vm, &top);
    if (result != VCVM_STATUS_SUCCESS)
    {
        return result;
    }

    result = vcvm_vm_pop(vm, &second);
    if (result != VCVM_STATUS_SUCCESS)
    {
        return result;
    }

    result = vcvm_vm_push(vm, top);
    if (result != VCVM_STATUS_SUCCESS)
    {
        return result;
    }

    return vcvm_vm_push(vm, second);
}

const vcvm_instruction_t VCVM_SWAP = {
    .name = "SWAP",
    .arity = 0,
    .handler = {
        .arity0 = &vcvm_swap,
    }
};

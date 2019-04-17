#include <vcvm/instruction.h>
#include <vcvm/error_codes.h>
#include <vcvm/vm.h>
#include <vcvm/stack_value.h>
#include <vpr/parameters.h>

int swap(vm_t* vm)
{
    int result;
    stack_value_t* left;
    stack_value_t* right;

    result = vm_pop(vm, &right);
    if (result != VCVM_STATUS_SUCCESS)
    {
        return result;
    }

    result = vm_pop(vm, &left);
    if (result != VCVM_STATUS_SUCCESS)
    {
        return result;
    }

    result = vm_push(vm, left);
    if (result != VCVM_STATUS_SUCCESS)
    {
        return result;
    }

    return vm_push(vm, right);
}
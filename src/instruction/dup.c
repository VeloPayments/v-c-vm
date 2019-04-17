#include <vcvm/instruction.h>
#include <vcvm/error_codes.h>
#include <vcvm/vm.h>
#include <vpr/parameters.h>

int dup(vm_t* vm)
{
    int result;
    stack_value_t* value;

    result = vm_pop(vm, &value);
    if (result != VCVM_STATUS_SUCCESS)
    {
        return result;
    }

    stack_value_t* copy = (stack_value_t*)allocate(vm->allocator_options, sizeof(stack_value_t));
    if (value == NULL)
    {
        result = VCVM_ERROR_CANT_ALLOCATE;
        goto done;
    }

    stack_value_init(copy, vm->allocator_options);
    result = stack_value_copy(copy, value);
    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    result = vm_push(vm, copy);
    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    result = vm_push(vm, value);

done:
    return result;
}
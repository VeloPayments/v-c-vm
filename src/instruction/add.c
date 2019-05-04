#include <vcvm/instruction.h>
#include <vcvm/error_codes.h>
#include <vcvm/vm.h>
#include <vcvm/stack_value.h>
#include <vpr/parameters.h>

int add(vm_t* vm)
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

    if (left->type != STACK_VALUE_TYPE_INTEGER || right->type != STACK_VALUE_TYPE_INTEGER)
    {
        return VCVM_ERROR_VM_BAD_TYPES;
    }

    stack_value_t* value = (stack_value_t*)allocate(vm->allocator_options, sizeof(stack_value_t));
    if (value == NULL)
    {
        return VCVM_ERROR_CANT_ALLOCATE;
    }

    stack_value_init(value, vm->allocator_options);
    stack_value_set_int(value, left->integer + right->integer);

    dispose((disposable_t*)left);
    dispose((disposable_t*)right);

    return vm_push(vm, value);
}


const instruction_t ADD = {
    .name = "ADD",
    .arity = 0,
    .handler = {
        .arity0 = &add,
    }
};

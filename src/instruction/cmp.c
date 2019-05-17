#include <vcvm/vm.h>
#include <vcvm/error_codes.h>
#include <vcvm/size.h>
#include <vpr/parameters.h>
#include <string.h>

int cmp(vm_t* vm)
{
    stack_value_t* left;
    stack_value_t* right;

    int result = vm_pop(vm, &left);
    if (result != VCVM_STATUS_SUCCESS)
    {
        return result;
    }

    result = vm_pop(vm, &right);
    if (result != VCVM_STATUS_SUCCESS)
    {
        return result;
    }

    if (left->type != right->type)
    {
        return VCVM_ERROR_VM_CANT_COMPARE_DIFFERENT_TYPES;
    }

    stack_value_t* comparison = allocate(vm->allocator_options, sizeof(stack_value_t));
    if (comparison == NULL)
    {
        return VCVM_ERROR_CANT_ALLOCATE;
    }

    stack_value_init(comparison, vm->allocator_options);

    if (left->type == STACK_VALUE_TYPE_STRING)
    {
        stack_value_set_int(comparison, strcmp(left->string, right->string));
        result = VCVM_STATUS_SUCCESS;
        goto done;
    }

    if (left->type == STACK_VALUE_TYPE_INTEGER)
    {
        if (left->integer > right->integer)
        {
            stack_value_set_int(comparison, 1);
        }
        else if (left->integer < right->integer)
        {
            stack_value_set_int(comparison, -1);
        }
        else
        {
            stack_value_set_int(comparison, 0);
        }
        result = VCVM_STATUS_SUCCESS;
        goto done;
    }

    if (left->type == STACK_VALUE_TYPE_UUID)
    {
        stack_value_set_int(comparison, memcmp(left->uuid, right->uuid, UUID_SIZE));
        result = VCVM_STATUS_SUCCESS;
        goto done;
    }

    result = VCVM_ERROR_VM_UNKNOWN_COMPARE;
    release(comparison->allocator_options, comparison);

done:
    dispose((disposable_t*)left);
    release(left->allocator_options, left);

    dispose((disposable_t*)right);
    release(right->allocator_options, right);

    return result;
}

const instruction_t CMP = {
    .name = "CMP",
    .arity = 0,
    .handler = {
        .arity0 = &cmp,
    }
};
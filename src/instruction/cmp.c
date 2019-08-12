#include <vcvm/vm.h>
#include <vcvm/error_codes.h>
#include <vcvm/size.h>
#include <string.h>

int cmp(vcvm_vm_t* vm)
{
    vcvm_stack_value_t* left;
    vcvm_stack_value_t* right;

    int result = vcvm_vm_pop(vm, &left);
    if (result != VCVM_STATUS_SUCCESS)
    {
        return result;
    }

    result = vcvm_vm_pop(vm, &right);
    if (result != VCVM_STATUS_SUCCESS)
    {
        return result;
    }

    if (left->type != right->type)
    {
        return VCVM_ERROR_VM_CANT_COMPARE_DIFFERENT_TYPES;
    }

    vcvm_stack_value_t* comparison = allocate(vm->allocator_options, sizeof(vcvm_stack_value_t));
    if (comparison == NULL)
    {
        return VCVM_ERROR_CANT_ALLOCATE;
    }

    vcvm_stack_value_init(comparison, vm->allocator_options);

    if (left->type == VCVM_STACK_VALUE_TYPE_STRING)
    {
        vcvm_stack_value_set_int(comparison, strcmp(left->string, right->string));
        result = VCVM_STATUS_SUCCESS;
        goto done;
    }

    if (left->type == VCVM_STACK_VALUE_TYPE_INTEGER)
    {
        if (left->integer > right->integer)
        {
            vcvm_stack_value_set_int(comparison, 1);
        }
        else if (left->integer < right->integer)
        {
            vcvm_stack_value_set_int(comparison, -1);
        }
        else
        {
            vcvm_stack_value_set_int(comparison, 0);
        }
        result = VCVM_STATUS_SUCCESS;
        goto done;
    }

    if (left->type == VCVM_STACK_VALUE_TYPE_UUID)
    {
        vcvm_stack_value_set_int(comparison, memcmp(left->uuid, right->uuid, UUID_SIZE));
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

const vcvm_instruction_t VCVM_CMP = {
    .name = "CMP",
    .arity = 0,
    .handler = {
        .arity0 = &cmp,
    }
};
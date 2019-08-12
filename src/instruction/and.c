#include <vcvm/instruction.h>
#include <vcvm/error_codes.h>
#include <vcvm/vm.h>
#include <vcvm/stack_value.h>

int vcvm_and(vcvm_vm_t* vm)
{
    int result;
    vcvm_stack_value_t* left;
    vcvm_stack_value_t* right;

    result = vcvm_vm_pop(vm, &right);
    if (result != VCVM_STATUS_SUCCESS)
    {
        return result;
    }

    result = vcvm_vm_pop(vm, &left);
    if (result != VCVM_STATUS_SUCCESS)
    {
        goto cleanup_right;
    }

    if (left->type != VCVM_STACK_VALUE_TYPE_INTEGER || right->type != VCVM_STACK_VALUE_TYPE_INTEGER)
    {
        result = VCVM_ERROR_VM_BAD_TYPES;
        goto cleanup_both;
    }

    vcvm_stack_value_t* value = (vcvm_stack_value_t*)allocate(vm->allocator_options, sizeof(vcvm_stack_value_t));
    if (value == NULL)
    {
        result = VCVM_ERROR_CANT_ALLOCATE;
        goto cleanup_both;
    }

    vcvm_stack_value_init(value, vm->allocator_options);
    vcvm_stack_value_set_int(value, left->integer & right->integer);

    result = vcvm_vm_push(vm, value);

cleanup_both:
    dispose((disposable_t*)left);
    release(left->allocator_options, left);

cleanup_right:
    dispose((disposable_t*)right);
    release(right->allocator_options, right);

    return result;
}

const vcvm_instruction_t VCVM_AND = {
    .name = "AND",
    .arity = 0,
    .handler = {
        .arity0 = &vcvm_and,
    }
};

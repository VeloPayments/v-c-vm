#include <vcvm/instruction.h>
#include <vcvm/error_codes.h>
#include <vcvm/vm.h>
#include <vpr/parameters.h>

int vcvm_dup(vcvm_vm_t* vm)
{
    int result;
    vcvm_stack_value_t* value;

    result = vcvm_vm_pop(vm, &value);
    if (result != VCVM_STATUS_SUCCESS)
    {
        return result;
    }

    vcvm_stack_value_t* copy = (vcvm_stack_value_t*)allocate(vm->allocator_options, sizeof(vcvm_stack_value_t));
    if (value == NULL)
    {
        result = VCVM_ERROR_CANT_ALLOCATE;
        goto done;
    }

    vcvm_stack_value_init(copy, vm->allocator_options);
    result = vcvm_stack_value_copy(copy, value);
    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    result = vcvm_vm_push(vm, copy);
    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    result = vcvm_vm_push(vm, value);

done:
    dispose((disposable_t*)value);
    release(value->allocator_options, value);

    return result;
}


const vcvm_instruction_t VCVM_DUP = {
    .name = "DUP",
    .arity = 0,
    .handler = {
        .arity0 = &vcvm_dup,
    }
};
#include <vcvm/instruction.h>
#include <vcvm/error_codes.h>
#include <vcvm/vm.h>
#include <vpr/parameters.h>

int vcvcvm_vm_pop(vcvm_vm_t* vm)
{
    vcvm_stack_value_t* value;
    int result = vcvm_vm_pop(vm, &value);
    if (result != VCVM_STATUS_SUCCESS)
    {
        return result;
    }
    dispose((disposable_t*)value);
    release(value->allocator_options, value);
    return VCVM_STATUS_SUCCESS;
}

const vcvm_instruction_t VCVM_POP = {
    .name = "POP",
    .arity = 0,
    .handler = {
        .arity0 = &vcvcvm_vm_pop,
    }
};
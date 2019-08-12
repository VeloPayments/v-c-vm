#include <vcvm/instruction.h>
#include <vcvm/error_codes.h>
#include <vcvm/vm.h>
#include <vcvm/stack_value.h>

int vcvm_load_const_string(vcvm_vm_t* vm, uint32_t a)
{
    if (a > vm->bytecode->string_count)
    {
        return VCVM_ERROR_VM_BAD_CONSTANT_COUNT;
    }

    vcvm_stack_value_t* value = (vcvm_stack_value_t*)allocate(vm->allocator_options, sizeof(vcvm_stack_value_t));
    if (value == NULL)
    {
        return VCVM_ERROR_CANT_ALLOCATE;
    }

    char* str = vm->bytecode->strings[a];

    vcvm_stack_value_init(value, vm->allocator_options);
    int result = vcvm_stack_value_set_string(value, str);
    if (result != VCVM_STATUS_SUCCESS)
    {
        return result;
    }

    return vcvm_vm_push(vm, value);
}

const vcvm_instruction_t VCVM_LOAD_CONST_STRING = {
    .name = "LOAD_CONST_STRING",
    .arity = 1,
    .handler = {
        .arity1 = &vcvm_load_const_string,
    }
};

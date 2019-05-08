#include <vcvm/instruction.h>
#include <vcvm/error_codes.h>
#include <vcvm/vm.h>
#include <vcvm/stack_value.h>
#include <vpr/parameters.h>

int load_const_int(vm_t* vm, uint32_t a)
{
    if (a > vm->bytecode->integer_count)
    {
        return VCVM_ERROR_VM_BAD_CONSTANT_COUNT;
    }

    stack_value_t* value = (stack_value_t*)allocate(vm->allocator_options, sizeof(stack_value_t));
    if (value == NULL)
    {
        return VCVM_ERROR_CANT_ALLOCATE;
    }

    int32_t number = vm->bytecode->integers[a];

    stack_value_init(value, vm->allocator_options);
    stack_value_set_int(value, number);

    return vm_push(vm, value);
}

const instruction_t LOAD_CONST_INT = {
    .name = "LOAD_CONST_INT",
    .arity = 1,
    .handler = {
        .arity1 = &load_const_int,
    }
};

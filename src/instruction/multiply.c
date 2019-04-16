#include <vcvm/instruction.h>
#include <vcvm/error_codes.h>
#include <vcvm/vm.h>
#include <vcvm/stack_value.h>
#include <vpr/parameters.h>

int multiply(vm_t* vm)
{
    stack_value_t* left = vm->stack[vm->sp - 1];
    stack_value_t* right = vm->stack[vm->sp];

    if (left->type != STACK_VALUE_TYPE_INTEGER || right->type != STACK_VALUE_TYPE_INTEGER)
    {
        return VCVM_VM_BAD_TYPES;
    }


    return VCVM_STATUS_SUCCESS;
}
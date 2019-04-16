#include <vcvm/instruction.h>
#include <vcvm/error_codes.h>
#include <vcvm/vm.h>
#include <vcvm/stack_value.h>
#include <vpr/parameters.h>

int swap(vm_t* vm)
{
    stack_value_t* top = vm->stack[vm->sp];
    stack_value_t* next = vm->stack[vm->sp - 1];

    vm->stack[vm->sp - 1] = top;
    vm->stack[vm->sp] = next;

    return VCVM_STATUS_SUCCESS;
}
#include <vcvm/vm.h>
#include <vcvm/error_codes.h>

int vcvm_vm_push(vcvm_vm_t* vm, vcvm_stack_value_t* value)
{
    if (vm->sp + 1 > MAX_STACK_SIZE)
    {
        return VCVM_ERROR_VM_STACKOVERFLOW;
    }

    vm->stack[vm->sp++] = value;
    return VCVM_STATUS_SUCCESS;
}
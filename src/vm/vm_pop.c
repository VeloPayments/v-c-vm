#include <vcvm/vm.h>
#include <vcvm/error_codes.h>

int vcvm_vm_pop(vcvm_vm_t* vm, vcvm_stack_value_t** value)
{
    if (vm->sp == 0)
    {
        return VCVM_ERROR_VM_STACKUNDERFLOW;
    }

    vm->sp--;
    *value = vm->stack[vm->sp];
    vm->stack[vm->sp] = NULL;
    return VCVM_STATUS_SUCCESS;
}
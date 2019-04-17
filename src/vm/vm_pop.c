#include <vcvm/vm.h>
#include <vcvm/error_codes.h>

int vm_pop(vm_t* vm, stack_value_t** value)
{
    if (vm->sp == 0)
    {
        return VCVM_ERROR_VM_STACKUNDERFLOW;
    }

    *value = vm->stack[vm->sp--];
    return VCVM_STATUS_SUCCESS;
}
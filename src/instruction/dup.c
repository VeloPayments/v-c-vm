#include <vcvm/instruction.h>
#include <vcvm/error_codes.h>
#include <vcvm/vm.h>
#include <vpr/parameters.h>

int dup(vm_t* vm)
{
    if (vm->sp + 1 >= MAX_STACK_SIZE)
    {
        return VCVM_ERROR_VM_STACKOVERFLOW;
    }

    vm->sp++;
    return VCVM_STATUS_SUCCESS;
}
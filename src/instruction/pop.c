#include <vcvm/instruction.h>
#include <vcvm/error_codes.h>
#include <vcvm/vm.h>
#include <vpr/parameters.h>

int pop(vm_t* vm)
{
    vm->sp--;
    return VCVM_STATUS_SUCCESS;
}
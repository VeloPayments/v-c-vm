#include <vcvm/instruction.h>
#include <vcvm/error_codes.h>
#include <vpr/parameters.h>

int halt(vm_t* UNUSED(vm))
{
    return VCVM_ERROR_VM_HALT;
}
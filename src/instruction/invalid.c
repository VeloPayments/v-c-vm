#include <vcvm/instruction.h>
#include <vcvm/error_codes.h>
#include <vpr/parameters.h>

int invalid(vm_t* UNUSED(vm))
{
    return VCVM_VM_INVALID_OPCODE;
}
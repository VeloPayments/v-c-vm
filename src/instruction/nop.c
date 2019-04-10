#include <vcvm/instruction.h>
#include <vcvm/error_codes.h>
#include <vpr/parameters.h>

int nop(vm_t* UNUSED(vm))
{
    // Guess what this does!
    return VCVM_STATUS_SUCCESS;
    // Nothing!
}
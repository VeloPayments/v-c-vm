#include <vcvm/vm.h>
#include <vcvm/error_codes.h>

int vm_run_til_complete(vcvm_vm_t* vm)
{
    int result;

    do
    {
        result = vcvm_vm_step(vm);
    } while (result == VCVM_STATUS_SUCCESS);

    return result;
}
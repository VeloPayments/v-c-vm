#include <vcvm/vm.h>
#include <vcvm/instruction.h>
#include <vcvm/error_codes.h>

int vcvm_vm_step(vcvm_vm_t* vm)
{
    int result;
    const vcvm_instruction_t* instr = vcvm_vm_decode_opcode(vm);
    switch (instr->arity)
    {
        case 0:
            result = vcvm_vm_decode_and_execute_arity_0(vm, instr);
            break;
        case 1:
            result = vcvm_vm_decode_and_execute_arity_1(vm, instr);
            break;
        case 2:
            result = vcvm_vm_decode_and_execute_arity_2(vm, instr);
            break;
        case 3:
            result = vcvm_vm_decode_and_execute_arity_3(vm, instr);
            break;
        default:
            result = VCVM_ERROR_VM_BAD_ARITY;
            break;
    }

    return result;
}
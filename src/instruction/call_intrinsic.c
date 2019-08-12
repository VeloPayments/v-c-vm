#include <vcvm/instruction.h>
#include <vcvm/error_codes.h>
#include <vcvm/vm.h>

int vcvm_call_intrinsic(vcvm_vm_t* vm, uint32_t a)
{
    if (a > vm->bytecode->intrinsics_count)
    {
        return VCVM_ERROR_VM_BAD_CONSTANT_COUNT;
    }

    const vcvm_intrinsic_t* intrinsic = vm->bytecode->intrinsics[a];

    if (vm->sp + intrinsic->nrets > MAX_STACK_SIZE)
    {
        return VCVM_ERROR_VM_STACKOVERFLOW;
    }

    if (vm->sp < intrinsic->nargs)
    {
        return VCVM_ERROR_VM_STACKUNDERFLOW;
    }

    return intrinsic->method(vm);
}


const vcvm_instruction_t VCVM_CALL_INTRINSIC = {
    .name = "CALL_INTRINSIC",
    .arity = 1,
    .handler = {
        .arity1 = &vcvm_call_intrinsic,
    }
};

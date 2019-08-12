#include <vcvm/instruction.h>
#include <vcvm/error_codes.h>
#include <vcvm/vm.h>

int call(vcvm_vm_t* vm, uint32_t a)
{
    if (a > vm->bytecode->jmp_count)
    {
        return VCVM_ERROR_VM_BAD_CONSTANT_COUNT;
    }

    uint32_t target = vm->bytecode->jmp_table[a];
    if (target < vm->ip)
    {
        return VCVM_ERROR_VM_CANT_JUMP_BACKWARDS;
    }

    if (target > vm->bytecode->instruction_count)
    {
        return VCVM_ERROR_VM_BAD_JMP;
    }

    // TODO: vcvm_add a callstack to track return locations

    vm->ip = target;

    return VCVM_ERROR_VM_HALT;
}

const vcvm_instruction_t VCVM_CALL = {
    .name = "CALL",
    .arity = 1,
    .handler = {
        .arity1 = &call,
    }
};
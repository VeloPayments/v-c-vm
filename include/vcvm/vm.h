#ifndef VCVM_VM_HEADER_GUARD
#define VCVM_VM_HEADER_GUARD

#define MAX_STACK_SIZE 16000

#include <vpr/disposable.h>
#include <vpr/allocator.h>
#include <stdint.h>
#include <vcvm/bytecode.h>
#include <vcvm/stack_value.h>
#include <vcvm/instruction.h>

/* make this header C++ friendly. */
#ifdef __cplusplus
extern "C" {
#endif  //__cplusplus

typedef struct vm
{
    disposable_t hdr;
    allocator_options_t* allocator_options;
    stack_value_t* stack[MAX_STACK_SIZE];
    bytecode_t* bytecode;
    uint32_t sp;
} vm_t;

int vm_init(vm_t* vm, allocator_options_t* allocator_options, bytecode_t* bytecode);
int vm_step(vm_t* vm);
instruction_t* vm_decode_opcode(vm_t* vm);
int vm_decode_and_execute_arity_1(vm_t* vm, const instruction_t* instr);
int vm_decode_and_execute_arity_2(vm_t* vm, const instruction_t* instr);
int vm_decode_and_execute_arity_3(vm_t* vm, const instruction_t* instr);
int vm_run_til_complete(void);

#ifdef __cplusplus
}
#endif  //__cplusplus

#endif

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

typedef struct vcvm_vm
{
    disposable_t hdr;
    allocator_options_t* allocator_options;
    vccert_parser_options_t* parser_options;
    vcvm_stack_value_t* stack[MAX_STACK_SIZE];
    vcvm_bytecode_t* bytecode;
    uint8_t* context_cert;
    uint32_t sp;
    uint32_t ip;
} vcvm_vm_t;

int vcvm_vm_init(vcvm_vm_t* vm, allocator_options_t* allocator_options, vccert_parser_options_t* parser_options, uint8_t* context_cert, vcvm_bytecode_t* bytecode);
int vcvm_vm_step(vcvm_vm_t* vm);
int vcvm_vm_pop(vcvm_vm_t* vm, vcvm_stack_value_t** value);
int vcvm_vm_push(vcvm_vm_t* vm, vcvm_stack_value_t* value);
const vcvm_instruction_t* vcvm_vm_decode_opcode(vcvm_vm_t* vm);
int vcvm_vm_decode_and_execute_arity_0(vcvm_vm_t* vm, const vcvm_instruction_t* instr);
int vcvm_vm_decode_and_execute_arity_1(vcvm_vm_t* vm, const vcvm_instruction_t* instr);
int vcvm_vm_decode_and_execute_arity_2(vcvm_vm_t* vm, const vcvm_instruction_t* instr);
int vcvm_vm_decode_and_execute_arity_3(vcvm_vm_t* vm, const vcvm_instruction_t* instr);
int vcvm_vm_run_til_complete(vcvm_vm_t* vm);

#ifdef __cplusplus
}
#endif  //__cplusplus

#endif

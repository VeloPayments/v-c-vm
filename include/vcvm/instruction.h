#ifndef VCVM_INSTRUCTION_H
#define VCVM_INSTRUCTION_H

#include <stdint.h>

/* make this header C++ friendly. */
#ifdef __cplusplus
extern "C" {
#endif  //__cplusplus

typedef struct vcvm_vm vcvm_vm_t;

typedef int (*arity0_t)(vcvm_vm_t* vm);
typedef int (*arity1_t)(vcvm_vm_t* vm, uint32_t a);
typedef int (*arity2_t)(vcvm_vm_t* vm, uint16_t a, uint16_t b);
typedef int (*arity3_t)(vcvm_vm_t* vm, uint8_t a, uint8_t b, uint8_t c);

typedef struct vcvm_instruction
{
    const char* name;
    const uint8_t arity;
    const union
    {
        arity0_t arity0;
        arity1_t arity1;
        arity2_t arity2;
        arity3_t arity3;
    } handler;
} vcvm_instruction_t;

int vcvm_nop(vcvm_vm_t* vm);
int vcvm_pop(vcvm_vm_t* vm);
int vcvm_invalid(vcvm_vm_t* vm);
int vcvm_halt(vcvm_vm_t* vm);
int vcvm_swap(vcvm_vm_t* vm);
int vcvm_dup(vcvm_vm_t* vm);

// Maths!
int vcvm_multiply(vcvm_vm_t* vm);
int vcvm_power(vcvm_vm_t* vm);
int vcvm_divide(vcvm_vm_t* vm);
int vcvm_modulo(vcvm_vm_t* vm);
int vcvm_add(vcvm_vm_t* vm);
int vcvm_subtract(vcvm_vm_t* vm);
int vcvm_lshift(vcvm_vm_t* vm);
int vcvm_rshift(vcvm_vm_t* vm);
int vcvm_and(vcvm_vm_t* vm);
int vcvm_or(vcvm_vm_t* vm);
int vcvm_xor(vcvm_vm_t* vm);
int vcvm_assert(vcvm_vm_t* vm);

int vcvm_load_const_string(vcvm_vm_t* vm, uint32_t a);
int vcvm_load_const_int(vcvm_vm_t* vm, uint32_t a);
int vcvm_load_const_uuid(vcvm_vm_t* vm, uint32_t a);
int vcvm_call_intrinsic(vcvm_vm_t* vm, uint32_t a);
int vcvm_push_context_cert(vcvm_vm_t* vm);

extern const vcvm_instruction_t VCVM_NOP;
extern const vcvm_instruction_t VCVM_INVALID;
extern const vcvm_instruction_t VCVM_HALT;
extern const vcvm_instruction_t VCVM_POP;
extern const vcvm_instruction_t VCVM_SWAP;
extern const vcvm_instruction_t VCVM_DUP;
extern const vcvm_instruction_t VCVM_MULTIPLY;
extern const vcvm_instruction_t VCVM_POWER;
extern const vcvm_instruction_t VCVM_DIVIDE;
extern const vcvm_instruction_t VCVM_MODULO;
extern const vcvm_instruction_t VCVM_ADD;
extern const vcvm_instruction_t VCVM_SUBTRACT;
extern const vcvm_instruction_t VCVM_LSHIFT;
extern const vcvm_instruction_t VCVM_RSHIFT;
extern const vcvm_instruction_t VCVM_AND;
extern const vcvm_instruction_t VCVM_OR;
extern const vcvm_instruction_t VCVM_XOR;
extern const vcvm_instruction_t VCVM_LOAD_CONST_STRING;
extern const vcvm_instruction_t VCVM_LOAD_CONST_INT;
extern const vcvm_instruction_t VCVM_LOAD_CONST_UUID;
extern const vcvm_instruction_t VCVM_CALL_INTRINSIC;
extern const vcvm_instruction_t VCVM_PUSH_CONTEXT_CERT;
extern const vcvm_instruction_t VCVM_ASSERT;
extern const vcvm_instruction_t VCVM_CMP;
extern const vcvm_instruction_t VCVM_CHECK_EQ;
extern const vcvm_instruction_t VCVM_CHECK_LT;
extern const vcvm_instruction_t VCVM_CHECK_GT;
extern const vcvm_instruction_t VCVM_PUSH_CONTEXT_KEYS;

extern const vcvm_instruction_t* vcvm_instructions[256];

#ifdef __cplusplus
}
#endif  //__cplusplus

#endif

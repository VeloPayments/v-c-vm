#ifndef VCVM_INSTRUCTION_H
#define VCVM_INSTRUCTION_H

#include <stdint.h>

/* make this header C++ friendly. */
#ifdef __cplusplus
extern "C" {
#endif  //__cplusplus

typedef struct vm vm_t;

typedef int (*arity0_t)(vm_t* vm);
typedef int (*arity1_t)(vm_t* vm, uint32_t a);
typedef int (*arity2_t)(vm_t* vm, uint16_t a, uint16_t b);
typedef int (*arity3_t)(vm_t* vm, uint8_t a, uint8_t b, uint8_t c);

typedef struct instruction
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
} instruction_t;

int nop(vm_t* vm);
int pop(vm_t* vm);
int invalid(vm_t* vm);
int halt(vm_t* vm);
int swap(vm_t* vm);
int dup(vm_t* vm);

// Maths!
int multiply(vm_t* vm);
int power(vm_t* vm);
int divide(vm_t* vm);
int modulo(vm_t* vm);
int add(vm_t* vm);
int subtract(vm_t* vm);
int lshift(vm_t* vm);
int rshift(vm_t* vm);
int and_(vm_t* vm);
int or_(vm_t* vm);
int xor_(vm_t* vm);

int load_const_string(vm_t* vm, uint32_t a);
int load_const_int(vm_t* vm, uint32_t a);
int load_const_uuid(vm_t *vm, uint32_t a);

int call_intrinsic(vm_t* vm, uint32_t a);

int push_context_cert(vm_t* vm);

extern const instruction_t NOP;
extern const instruction_t INVALID;
extern const instruction_t HALT;
extern const instruction_t POP;
extern const instruction_t SWAP;
extern const instruction_t DUP;
extern const instruction_t MULTIPLY;
extern const instruction_t POWER;
extern const instruction_t DIVIDE;
extern const instruction_t MODULO;
extern const instruction_t ADD;
extern const instruction_t SUBTRACT;
extern const instruction_t LSHIFT;
extern const instruction_t RSHIFT;
extern const instruction_t AND_;
extern const instruction_t OR_;
extern const instruction_t XOR_;
extern const instruction_t LOAD_CONST_STRING;
extern const instruction_t LOAD_CONST_INT;
extern const instruction_t LOAD_CONST_UUID;
extern const instruction_t CALL_INTRINSIC;
extern const instruction_t PUSH_CONTEXT_CERT;

extern const instruction_t* instructions[256];

#ifdef __cplusplus
}
#endif  //__cplusplus

#endif

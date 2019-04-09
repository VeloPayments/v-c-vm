#ifndef VCVM_INSTRUCTION_H
#define VCVM_INSTRUCTION_H

#include <stdint.h>

/* make this header C++ friendly. */
#ifdef __cplusplus
extern "C" {
#endif  //__cplusplus

typedef int (*arity0_t)();
typedef int (*arity1_t)(uint32_t a);
typedef int (*arity2_t)(uint16_t a, uint16_t b);
typedef int (*arity3_t)(uint8_t a, uint8_t b, uint8_t c);

typedef struct instruction {
    const uint8_t arity;
    const union {
        arity0_t arity0;
        arity1_t arity1;
        arity2_t arity2;
        arity3_t arity3;
    } decode_and_execute;
} instruction_t;

#ifdef __cplusplus
}
#endif  //__cplusplus

#endif

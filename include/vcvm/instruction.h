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
int load_const_artifact(vm_t* vm, uint32_t a);

int call_intrinsic(vm_t* vm, uint32_t a);

const instruction_t NOP = {
    .arity = 0,
    .handler = {
        .arity0 = &nop,
    }
};

const instruction_t INVALID = {
    .arity = 0,
    .handler = {
        .arity0 = &invalid,
    }
};

const instruction_t HALT = {
    .arity = 0,
    .handler = {
        .arity0 = &halt,
    }
};

const instruction_t POP = {
    .arity = 0,
    .handler = {
        .arity0 = &pop,
    }
};

const instruction_t SWAP = {
    .arity = 0,
    .handler = {
        .arity0 = &swap,
    }
};

const instruction_t DUP = {
    .arity = 0,
    .handler = {
        .arity0 = &dup,
    }
};

const instruction_t MULTIPLY = {
    .arity = 0,
    .handler = {
        .arity0 = &multiply,
    }
};

const instruction_t POWER = {
    .arity = 0,
    .handler = {
        .arity0 = &power,
    }
};

const instruction_t DIVIDE = {
    .arity = 0,
    .handler = {
        .arity0 = &divide,
    }
};

const instruction_t MODULO = {
    .arity = 0,
    .handler = {
        .arity0 = &modulo,
    }
};

const instruction_t ADD = {
    .arity = 0,
    .handler = {
        .arity0 = &add,
    }
};

const instruction_t SUBTRACT = {
    .arity = 0,
    .handler = {
        .arity0 = &subtract,
    }
};

const instruction_t LSHIFT = {
    .arity = 0,
    .handler = {
        .arity0 = &lshift,
    }
};

const instruction_t RSHIFT = {
    .arity = 0,
    .handler = {
        .arity0 = &rshift,
    }
};

const instruction_t AND_ = {
    .arity = 0,
    .handler = {
        .arity0 = &and_,
    }
};

const instruction_t OR_ = {
    .arity = 0,
    .handler = {
        .arity0 = &or_,
    }
};

const instruction_t XOR_ = {
    .arity = 0,
    .handler = {
        .arity0 = &xor_,
    }
};

const instruction_t LOAD_CONST_STRING = {
    .arity = 1,
    .handler = {
        .arity1 = &load_const_string,
    }
};

const instruction_t LOAD_CONST_INT = {
    .arity = 1,
    .handler = {
        .arity1 = &load_const_int,
    }
};

const instruction_t LOAD_CONST_ARTIFACT = {
    .arity = 1,
    .handler = {
        .arity1 = &load_const_artifact,
    }
};

const instruction_t CALL_INTRINSIC = {
    .arity = 1,
    .handler = {
        .arity1 = &call_intrinsic,
    }
};

#ifdef __cplusplus
}
#endif  //__cplusplus

#endif

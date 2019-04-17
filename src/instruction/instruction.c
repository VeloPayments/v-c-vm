#include <vcvm/instruction.h>

const instruction_t NOP = {
    .name = "NOP",
    .arity = 0,
    .handler = {
        .arity0 = &nop,
    }
};

const instruction_t INVALID = {
    .name = "INVALID",
    .arity = 0,
    .handler = {
        .arity0 = &invalid,
    }
};

const instruction_t HALT = {
    .name = "HALT",
    .arity = 0,
    .handler = {
        .arity0 = &halt,
    }
};

const instruction_t POP = {
    .name = "POP",
    .arity = 0,
    .handler = {
        .arity0 = &pop,
    }
};

const instruction_t SWAP = {
    .name = "SWAP",
    .arity = 0,
    .handler = {
        .arity0 = &swap,
    }
};

const instruction_t DUP = {
    .name = "DUP",
    .arity = 0,
    .handler = {
        .arity0 = &dup,
    }
};

const instruction_t MULTIPLY = {
    .name = "MULTIPLY",
    .arity = 0,
    .handler = {
        .arity0 = &multiply,
    }
};

const instruction_t POWER = {
    .name = "POWER",
    .arity = 0,
    .handler = {
        .arity0 = &power,
    }
};

const instruction_t DIVIDE = {
    .name = "DIVIDE",
    .arity = 0,
    .handler = {
        .arity0 = &divide,
    }
};

const instruction_t MODULO = {
    .name = "MODULO",
    .arity = 0,
    .handler = {
        .arity0 = &modulo,
    }
};

const instruction_t ADD = {
    .name = "ADD",
    .arity = 0,
    .handler = {
        .arity0 = &add,
    }
};

const instruction_t SUBTRACT = {
    .name = "SUBTRACT",
    .arity = 0,
    .handler = {
        .arity0 = &subtract,
    }
};

const instruction_t LSHIFT = {
    .name = "LSHIFT",
    .arity = 0,
    .handler = {
        .arity0 = &lshift,
    }
};

const instruction_t RSHIFT = {
    .name = "RSHIFT",
    .arity = 0,
    .handler = {
        .arity0 = &rshift,
    }
};

const instruction_t AND_ = {
    .name = "AND_",
    .arity = 0,
    .handler = {
        .arity0 = &and_,
    }
};

const instruction_t OR_ = {
    .name = "OR_",
    .arity = 0,
    .handler = {
        .arity0 = &or_,
    }
};

const instruction_t XOR_ = {
    .name = "XOR_",
    .arity = 0,
    .handler = {
        .arity0 = &xor_,
    }
};

const instruction_t LOAD_CONST_STRING = {
    .name = "LOAD_CONST_STRING",
    .arity = 1,
    .handler = {
        .arity1 = &load_const_string,
    }
};

const instruction_t LOAD_CONST_INT = {
    .name = "LOAD_CONST_INT",
    .arity = 1,
    .handler = {
        .arity1 = &load_const_int,
    }
};

const instruction_t LOAD_CONST_ARTIFACT = {
    .name = "LOAD_CONST_ARTIFACT",
    .arity = 1,
    .handler = {
        .arity1 = &load_const_artifact,
    }
};

const instruction_t CALL_INTRINSIC = {
    .name = "CALL_INTRINSIC",
    .arity = 1,
    .handler = {
        .arity1 = &call_intrinsic,
    }
};

const instruction_t* opcodes[256] = {
    &NOP,
    &POP,
    &SWAP,
    &DUP,
    &MULTIPLY,
    &POWER,
    &DIVIDE,
    &MODULO,
    &ADD,
    &SUBTRACT,
    &LSHIFT,
    &RSHIFT,
    &AND_,
    &OR_,
    &XOR_,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &LOAD_CONST_STRING,  // 64 - 1 opcode args
    &LOAD_CONST_INT,
    &LOAD_CONST_ARTIFACT,
    &CALL_INTRINSIC,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,  // 2 arity args
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,  // 3 arity.
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &INVALID,
    &HALT,
};
#ifndef VCVM_OPCODE_H
#define VCVM_OPCODE_H

#include <vcvm/instruction.h>

/* make this header C++ friendly. */
#ifdef __cplusplus
extern "C" {
#endif  //__cplusplus

const instruction_t opcodes[10] = {
        {
                .arity = 0,
                .decode_and_execute.arity0 = NULL,
        }
};

#ifdef __cplusplus
}
#endif  //__cplusplus

#endif //VCVM_OPCODE_H

#ifndef VCVM_VM_HEADER_GUARD
#define VCVM_VM_HEADER_GUARD

#define MAX_STACK_SIZE 16000

#include <vpr/disposable.h>
#include <vpr/allocator.h>
#include <stdint.h>
#include <vcvm/bytecode.h>
#include <vcvm/stack_value.h>

/* make this header C++ friendly. */
#ifdef __cplusplus
extern "C" {
#endif  //__cplusplus

typedef struct vm
{
    disposable_t hdr;
    allocator_options_t* allocator_options;
    uint32_t sp;
    bytecode_t* bytecode;
    stack_value_t* stack[MAX_STACK_SIZE];
} vm_t;

int vm_init(allocator_options_t* allocator_options, bytecode_t* bytecode);


#ifdef __cplusplus
}
#endif  //__cplusplus

#endif

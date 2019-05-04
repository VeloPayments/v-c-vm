#ifndef VCVM_BYTECODE_HEADER_GUARD
#define VCVM_BYTECODE_HEADER_GUARD

#include <stdint.h>
#include <vcvm/intrinsic.h>
#include <vpr/disposable.h>
#include <vpr/allocator.h>
#include <vpr/dynamic_array.h>
#include <vpr/hashmap.h>

/* make this header C++ friendly. */
#ifdef __cplusplus
extern "C" {
#endif  //__cplusplus

typedef struct bytecode
{
    disposable_t hdr;
    allocator_options_t* allocator_options;

    uint32_t magic;

    uint32_t integer_count;
    int32_t* integers;

    uint32_t string_count;
    char** strings;

    uint32_t artifact_count;
    uint8_t** artifacts;

    uint32_t intrinsics_count;
    const intrinsic_t** intrinsics;

    uint32_t instruction_count;
    uint32_t* instructions;
} bytecode_t;

int bytecode_init(bytecode_t* bytecode, allocator_options_t* allocator_options, const uint8_t* raw, size_t size, resolve_intrinsic_delegate_t resolve);

#ifdef __cplusplus
}
#endif  //__cplusplus

#endif

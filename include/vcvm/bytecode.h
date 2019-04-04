#ifndef VCVM_BYTECODE_HEADER_GUARD
#define VCVM_BYTECODE_HEADER_GUARD

#include <stdint.h>
#include <vcvm/intrinsic.h>
#include <vpr/disposable.h>
#include <vpr/allocator.h>

/* make this header C++ friendly. */
#ifdef __cplusplus
extern "C" {
#endif  //__cplusplus

typedef struct bytecode
{
    disposable_t hdr;
    allocator_options_t* allocator_options;

    uint32_t magic;

    // Integer constants.
    uint32_t integer_count;
    uint32_t* integers;

    // String constants.
    uint32_t string_count;
    char** strings;

    // Artifacts (UUIDs)
    uint32_t artifact_count;
    uint8_t** artifacts;

    // Intrinsics.
    uint32_t intrinsics_count;
    intrinsic_t** intrinsics;

    // Instructions.
    uint32_t instruction_count;
    uint32_t* instructions;
} bytecode_t;

int bytecode_init(bytecode_t* bytecode, allocator_options_t* allocator_options, const uint8_t* raw, size_t size);

#ifdef __cplusplus
}
#endif  //__cplusplus

#endif

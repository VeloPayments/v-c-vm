#ifndef VCVM_BUILDER_HEADER_GUARD
#define VCVM_BUILDER_HEADER_GUARD

/* make this header C++ friendly. */
#include <vpr/disposable.h>
#include <vpr/allocator.h>
#include <vpr/dynamic_array.h>
#include <vcvm/intrinsic.h>

// This is entirely arbitrary.
#define MAX_CONSTANTS 256

#ifdef __cplusplus
extern "C" {
#endif  //__cplusplus

typedef struct bytecode_builder_context
{
    disposable_t hdr;
    allocator_options_t* allocator_options;

    /*
     * TODO Replace this with a hashmap implementation
     * This is really bad for performance but it keeps the code clean for now.
     */

    uint32_t string_count;
    dynamic_array_options_t* string_options;
    dynamic_array_t* strings;

    uint32_t intrinsic_count;
    dynamic_array_options_t* intrinsics_options;
    dynamic_array_t* intrinsics;

    uint32_t artifact_count;
    dynamic_array_options_t* artifacts_options;
    dynamic_array_t* artifacts;

    uint32_t integer_count;
    dynamic_array_options_t* integers_options;
    dynamic_array_t* integers;
} bytecode_builder_context_t;

int bytecode_builder_init(bytecode_builder_context_t* builder, allocator_options_t* allocator);

int bytecode_builder_add_string(bytecode_builder_context_t* builder, char* string);
int bytecode_builder_add_int(bytecode_builder_context_t* builder, int32_t num);
int bytecode_builder_add_artifact(bytecode_builder_context_t* builder, uint8_t* artifact_uuid);
int bytecode_builder_add_intrinsic(bytecode_builder_context_t* builder, const intrinsic_t* intrinsic);
int bytecode_builder_add_instruction(bytecode_builder_context_t* builder, uint32_t instruction);

size_t bytecode_builder_total_size(bytecode_builder_context_t* builder);
int bytecode_builder_emit(bytecode_builder_context_t* builder, uint8_t* bytes, size_t size);

#ifdef __cplusplus
}
#endif  //__cplusplus

#endif
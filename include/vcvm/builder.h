#ifndef VCVM_BUILDER_HEADER_GUARD
#define VCVM_BUILDER_HEADER_GUARD

/* make this header C++ friendly. */
#include <vpr/disposable.h>
#include <vpr/allocator.h>
#include <vcvm/intrinsic.h>
#include <vpr/hashmap.h>
#include <stdbool.h>
#include <vpr/dynamic_array.h>

// This is entirely arbitrary.
#define MAX_CONSTANTS 256
#define MAX_INSTRUCTIONS 512

#ifdef __cplusplus
extern "C" {
#endif  //__cplusplus

typedef struct bytecode_builder
{
    disposable_t hdr;
    allocator_options_t* allocator_options;

    uint32_t string_count;
    hashmap_options_t string_options;
    hashmap_t strings;

    uint32_t intrinsic_count;
    hashmap_options_t intrinsics_options;
    hashmap_t intrinsics;

    uint32_t artifact_count;
    hashmap_options_t artifacts_options;
    hashmap_t artifacts;

    uint32_t integer_count;
    hashmap_options_t integers_options;
    hashmap_t integers;

    uint32_t intruction_count;
    dynamic_array_options_t instructions_options;
    dynamic_array_t instructions;

} bytecode_builder_t;

typedef struct string_constant {
    uint32_t index;
    char* value;
} string_constant_t;

typedef struct int_constant {
    uint32_t index;
    int32_t value;
} integer_constant_t;

typedef struct uuid_constant {
    uint32_t index;
    uint8_t* value;
} uuid_constant_t;

typedef struct intrinsic_constant {
    uint32_t index;
    intrinsic_t* value;
} intrinsic_constant_t;

int bytecode_builder_init(bytecode_builder_t* builder, allocator_options_t* allocator);

int bytecode_builder_add_string(bytecode_builder_t* builder, char* string);
int bytecode_builder_add_int(bytecode_builder_t* builder, int32_t num);
int bytecode_builder_add_artifact(bytecode_builder_t* builder, uint8_t* artifact_uuid);
int bytecode_builder_add_intrinsic(bytecode_builder_t* builder, const intrinsic_t* intrinsic);
int bytecode_builder_add_instruction(bytecode_builder_t* builder, uint32_t instruction);

size_t bytecode_builder_total_size(bytecode_builder_t* builder);
int bytecode_builder_emit(bytecode_builder_t* builder, uint8_t* bytes, size_t size);



#ifdef __cplusplus
}
#endif  //__cplusplus

#endif
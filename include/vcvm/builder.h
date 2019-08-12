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
#define MAX_JMPS 256

#ifdef __cplusplus
extern "C" {
#endif  //__cplusplus

typedef struct vcvm_bytecode_builder
{
    disposable_t hdr;
    allocator_options_t* allocator_options;

    uint32_t string_count;
    uint32_t string_size;
    hashmap_options_t string_options;
    hashmap_t strings;

    uint32_t intrinsic_count;
    hashmap_options_t intrinsics_options;
    hashmap_t intrinsics;

    uint32_t uuid_count;
    hashmap_options_t uuid_options;
    hashmap_t uuids;

    uint32_t integer_count;
    hashmap_options_t integers_options;
    hashmap_t integers;

    uint32_t jmp_count;
    hashmap_options_t jmp_options;
    hashmap_t jmp_table;

    uint32_t instruction_count;
    dynamic_array_options_t instructions_options;
    dynamic_array_t instructions;
} vcvm_bytecode_builder_t;

typedef struct vcvm_string_constant
{
    uint32_t index;
    char* value;
} vcvm_string_constant_t;

typedef struct vcvm_int_constant
{
    uint32_t index;
    int32_t value;
} vcvm_integer_constant_t;

typedef struct vcvm_uuid_constant
{
    uint32_t index;
    uint8_t* value;
} vcvm_uuid_constant_t;

typedef struct vcvm_intrinsic_constant
{
    uint32_t index;
    const vcvm_intrinsic_t* value;
} vcvm_intrinsic_constant_t;

typedef struct vcvm_function_constant
{
    uint32_t index;
    char* value;
    uint32_t pc;
} vcvm_function_constant_t;

int vcvm_bytecode_builder_init(vcvm_bytecode_builder_t* builder, allocator_options_t* allocator);

int vcvm_bytecode_builder_add_string(vcvm_bytecode_builder_t* builder, char* string);
int vcvm_bytecode_builder_add_int(vcvm_bytecode_builder_t* builder, int32_t num);
int vcvm_bytecode_builder_add_uuid(vcvm_bytecode_builder_t* builder, uint8_t* uuid);
int vcvm_bytecode_builder_add_intrinsic(vcvm_bytecode_builder_t* builder, const vcvm_intrinsic_t* intrinsic);
int vcvm_bytecode_builder_add_instruction(vcvm_bytecode_builder_t* builder, uint32_t instruction);

size_t vcvm_bytecode_builder_total_size(vcvm_bytecode_builder_t* builder);
int vcvm_bytecode_builder_emit(vcvm_bytecode_builder_t* builder, uint8_t* bytes, size_t size, size_t* written);


#ifdef __cplusplus
}
#endif  //__cplusplus

#endif
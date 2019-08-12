#ifndef VCVM_BYTECODE_INTERNAL_HEADER_GUARD
#define VCVM_BYTECODE_INTERNAL_HEADER_GUARD

#include <stdint.h>
#include <stddef.h>
#include <vcvm/bytecode.h>

/* make this header C++ friendly. */
#ifdef __cplusplus
extern "C" {
#endif  //__cplusplus

int bytecode_read_uint8(uint8_t* out, const uint8_t* raw, size_t size, size_t* offset);
int bytecode_read_uint32(uint32_t* out, const uint8_t* raw, size_t size, size_t* offset);
int bytecode_read_int32(int32_t* out, const uint8_t* raw, size_t size, size_t* offset);
int bytecode_read_string(char* str, size_t str_size, const uint8_t* raw, size_t size, size_t* offset);
int bytecode_read_uuid(uint8_t* uuid, const uint8_t* raw, size_t size, size_t* offset);

int bytecode_read_instructions(vcvm_bytecode_t* bytecode, const uint8_t* raw, size_t size, size_t* offset);
int bytecode_read_string_constants(vcvm_bytecode_t* bytecode, const uint8_t* raw, size_t size, size_t* offset);
int bytecode_read_integer_constants(vcvm_bytecode_t* bytecode, const uint8_t* raw, size_t size, size_t* offset);
int bytecode_read_uuid_constants(vcvm_bytecode_t* bytecode, const uint8_t* raw, size_t size, size_t* offset);
int bytecode_read_intrinsic_constants(vcvm_bytecode_t* bytecode, const uint8_t* raw, size_t size, size_t* offset, vcvm_resolve_intrinsic_delegate_t pFunction);
int bytecode_read_jmptable(vcvm_bytecode_t* bytecode, const uint8_t* raw, size_t size, size_t* offset);

void vcvm_bytecode_dispose_instructions(vcvm_bytecode_t* bytecode);
void bytecode_dispose_string_constants(vcvm_bytecode_t* bytecode);
void bytecode_dispose_integer_constants(vcvm_bytecode_t* bytecode);
void bytecode_dispose_uuid_constants(vcvm_bytecode_t* bytecode);
void bytecode_dispose_intrinsic_constants(vcvm_bytecode_t* bytecode);
void bytecode_dispose_jmptable(vcvm_bytecode_t* bytecode);

#ifdef __cplusplus
}
#endif  //__cplusplus

#endif

#ifndef BUILD_BYTECODE_INTERNAL_HEADER_GUARD
#define BUILD_BYTECODE_INTERNAL_HEADER_GUARD

#include <stdint.h>
#include <stddef.h>
#include <vcvm/bytecode.h>

/* make this header C++ friendly. */
#ifdef __cplusplus
extern "C" {
#endif  //__cplusplus

int bytecode_read_uint32(uint32_t* num, const uint8_t* raw, size_t size, size_t* offset);
int bytecode_read_string(char* str, size_t str_size, const uint8_t* raw, size_t size, size_t* offset);

int bytecode_read_string_constants(bytecode_t* bytecode, const uint8_t* raw, size_t size, size_t* offset);
int bytecode_read_integer_constants(bytecode_t* bytecode, const uint8_t* raw, size_t size, size_t* offset);


#ifdef __cplusplus
}
#endif  //__cplusplus

#endif

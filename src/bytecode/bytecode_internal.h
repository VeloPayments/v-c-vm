#ifndef BUILD_BYTECODE_INTERNAL_HEADER_GUARD
#define BUILD_BYTECODE_INTERNAL_HEADER_GUARD

#include <stdint.h>
#include <stddef.h>

/* make this header C++ friendly. */
# ifdef     __cplusplus
extern "C" {
#endif    //__cplusplus

int bytecode_read_magic(uint32_t *magic_number, const uint8_t *raw, size_t length);

# ifdef     __cplusplus
}
#endif    //__cplusplus

#endif

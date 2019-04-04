#ifndef VCVM_UUID_HEADER_GUARD
#define VCVM_UUID_HEADER_GUARD

#include <stdint.h>

/* make this header C++ friendly. */
#ifdef __cplusplus
extern "C" {
#endif  //__cplusplus

typedef uint8_t uuid_t[16];

#ifdef __cplusplus
}
#endif  //__cplusplus

#endif

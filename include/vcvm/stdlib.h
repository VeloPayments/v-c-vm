#ifndef VCVM_STDLIB_HEADER_GUARD
#define VCVM_STDLIB_HEADER_GUARD

#include <vcvm/intrinsic.h>

/* make this header C++ friendly. */
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

extern const intrinsic_t STRING_CONTAINS;
extern const intrinsic_t STRING_EQUALS;
extern const intrinsic_t LOAD_ARTIFACT;
extern const intrinsic_t LONGCODE_TO_SHORTCODE;

#ifdef __cplusplus
}
#endif //__cplusplus

#endif
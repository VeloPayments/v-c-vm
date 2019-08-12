#ifndef VCVM_STDLIB_HEADER_GUARD
#define VCVM_STDLIB_HEADER_GUARD

#include <vcvm/intrinsic.h>

/* make this header C++ friendly. */
#ifdef __cplusplus
extern "C" {
#endif  //__cplusplus

extern const vcvm_intrinsic_t VCVM_STRING_CONTAINS;
extern const vcvm_intrinsic_t VCVM_STRING_EQUALS;
extern const vcvm_intrinsic_t VCVM_LOAD_ARTIFACT;
extern const vcvm_intrinsic_t VCVM_LONGCODE_TO_SHORTCODE;

#ifdef __cplusplus
}
#endif  //__cplusplus

#endif
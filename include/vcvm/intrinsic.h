#ifndef VCVM_INTRINSIC_HEADER_GUARD
#define VCVM_INTRINSIC_HEADER_GUARD

#include <vpr/allocator.h>
#include <vpr/disposable.h>
#include <stdint.h>

/* make this header C++ friendly. */
#ifdef __cplusplus
extern "C" {
#endif  //__cplusplus

typedef struct vm vm_t;

typedef int (*intrinsic_method_t)(vm_t* vm);

typedef struct intrinsic
{
    uint8_t* uuid;
    uint32_t nargs;
    uint32_t nrets;
    intrinsic_method_t method;
} intrinsic_t;

typedef int (*resolve_intrinsic_delegate_t)(const intrinsic_t ** intrinsic, uint8_t* uuid, uint32_t nargs, uint32_t nrets);

#ifdef __cplusplus
}
#endif  //__cplusplus

#endif

#ifndef VCVM_INTRINSIC_HEADER_GUARD
#define VCVM_INTRINSIC_HEADER_GUARD

#include <vpr/allocator.h>
#include <vpr/disposable.h>
#include <stdint.h>

/* make this header C++ friendly. */
#ifdef __cplusplus
extern "C" {
#endif  //__cplusplus

typedef struct vcvm_vm vcvm_vm_t;

typedef int (*vcvm_intrinsic_method_t)(vcvm_vm_t* vm);

typedef struct vcvm_intrinsic
{
    uint8_t* uuid;
    uint32_t nargs;
    uint32_t nrets;
    vcvm_intrinsic_method_t method;
} vcvm_intrinsic_t;

typedef int (*vcvm_resolve_intrinsic_delegate_t)(const vcvm_intrinsic_t** intrinsic, uint8_t* uuid, uint32_t nargs, uint32_t nrets);

#ifdef __cplusplus
}
#endif  //__cplusplus

#endif

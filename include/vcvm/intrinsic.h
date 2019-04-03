#ifndef VCVM_INTRINSIC_HEADER_GUARD
#define VCVM_INTRINSIC_HEADER_GUARD

#include <vcvm/uuid.h>
#include <vpr/disposable.h>
#include <stdint.h>

/* make this header C++ friendly. */
# ifdef     __cplusplus
extern "C" {
#endif    //__cplusplus

typedef struct vm vm_t;
typedef int (*intrinsic_method_t)(vm_t *vm, uint32_t argc, uint32_t* argv);

typedef struct intrinsic
{
    disposable_t hdr;
    uuid_t* uuid;
    uint32_t nargs;
    uint32_t nrets;
    intrinsic_method_t method;
} intrinsic_t;

int intrinsic_init(intrinsic_t* intrinsic, uuid_t* uuid, uint32_t nargs, uint32_t nrets, intrinsic_method_t method);

# ifdef     __cplusplus
}
#endif    //__cplusplus

#endif

#ifndef VCVM_INTRINSIC_HEADER_GUARD
#define VCVM_INTRINSIC_HEADER_GUARD

#include <vcvm/vm.h>

/* make this header C++ friendly. */
# ifdef     __cplusplus
extern "C" {
#endif    //__cplusplus

typedef int (*intrinsic_method_t)(vm_t *vm, uint32_t argc, uint32_t* argv);

typedef struct intrinsic
{
    intrinsic_method_t method;
    uint32_t nargs;
    uint32_t nrets;
} intrinsic_t;

# ifdef     __cplusplus
}
#endif    //__cplusplus

#endif

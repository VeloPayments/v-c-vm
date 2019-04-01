#ifndef VCVM_VM_HEADER_GUARD
#define VCVM_VM_HEADER_GUARD

/* make this header C++ friendly. */
# ifdef     __cplusplus
extern "C" {
#endif    //__cplusplus

typedef struct vm
{
    uint32_t sp;
} vm_t;



# ifdef     __cplusplus
}
#endif    //__cplusplus

#endif

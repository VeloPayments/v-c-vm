#ifndef VCVM_SIZE_HEADER_GUARD
#define VCVM_SIZE_HEADER_GUARD

/* make this header C++ friendly. */
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#define UUID_SIZE 16
#define INTRINSIC_SIZE (UUID_SIZE + sizeof(uint32_t) + sizeof(uint32_t))

#ifdef __cplusplus
}
#endif //__cplusplus


#endif
#ifndef BUILD_ERROR_CODES_HEADER_GUARD
#define BUILD_ERROR_CODES_HEADER_GUARD

/* make this header C++ friendly. */
#ifdef __cplusplus
extern "C" {
#endif  //__cplusplus

#define VCVM_STATUS_SUCCESS 0x0000

#define VCVM_BYTECODE_NOT_ENOUGH_BYTES 0x1000

#define VCVM_BYTECODE_BAD_MAGIC 0x1001

#define VCVM_INTRINSIC_NOT_FOUND 0x2000

#define VCVM_VM_BAD_ARITY 0x3001

#define VCVM_CANT_ALLOCATE 0xF000

#ifdef __cplusplus
}
#endif  //__cplusplus

#endif

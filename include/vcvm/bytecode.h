#ifndef BUILD_BYTECODE_HEADER_GUARD
#define BUILD_BYTECODE_HEADER_GUARD

/* make this header C++ friendly. */
# ifdef     __cplusplus
extern "C" {
#endif    //__cplusplus

/*
 * typedef struct bytecode {
    uint32_t magic_number; // Should be 0xDECAF.
    uint32_t string_const_count;
    char* string_consts[string_const_count];
    uint32_t uuid_const_count;
    uint8_t* uuid_consts[uuid_const_count];
    uint32_t int_const_count;
    uint32_t* int_consts[int_const_count];
    uint32_t intrinsic_const_count;
    intrinsic_t intrinsic_consts[intrinsic_const_count];
    uint32_t instruction_count;
    uint32_t instructions[instruction_count];
} bytecode_t;
 */

typedef struct bytecode {
    uint32_t magic;
    uint32_t instruction_count;
    uint32_t* instructions;
    int

} bytecode_t;

# ifdef     __cplusplus
}
#endif    //__cplusplus

#endif

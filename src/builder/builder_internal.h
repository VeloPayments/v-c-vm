#ifndef VCVM_BUILDER_INTERNAL_HEADER_GUARD
#define VCVM_BUILDER_INTERNAL_HEADER_GUARD

/* make this header C++ friendly. */
#ifdef __cplusplus
extern "C" {
#endif  //__cplusplus

int bytecode_builder_write_integer_constants(bytecode_builder_t* builder, uint8_t* byte, size_t* offset);
int bytecode_builder_write_string_constants(bytecode_builder_t* builder, uint8_t* byte, size_t* offset);
int bytecode_builder_write_uuid_constants(bytecode_builder_t* builder, uint8_t* byte, size_t* offset);
int bytecode_builder_write_intrinsic_constants(bytecode_builder_t* builder, uint8_t* byte, size_t* offset);
int bytecode_builder_write_instructions(bytecode_builder_t* builder, uint8_t* byte, size_t* offset);

#ifdef __cplusplus
}
#endif  //__cplusplus


#endif
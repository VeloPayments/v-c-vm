#ifndef VCVM_BUILDER_INTERNAL_HEADER_GUARD
#define VCVM_BUILDER_INTERNAL_HEADER_GUARD

/* make this header C++ friendly. */
#ifdef __cplusplus
extern "C" {
#endif  //__cplusplus

int vcvm_bytecode_builder_write_integer_constants(vcvm_bytecode_builder_t* builder, uint8_t* byte, size_t* offset);
int vcvm_bytecode_builder_write_string_constants(vcvm_bytecode_builder_t* builder, uint8_t* byte, size_t* offset);
int vcvm_bytecode_builder_write_uuid_constants(vcvm_bytecode_builder_t* builder, uint8_t* byte, size_t* offset);
int vcvm_bytecode_builder_write_intrinsic_constants(vcvm_bytecode_builder_t* builder, uint8_t* byte, size_t* offset);
int vcvm_bytecode_builder_write_instructions(vcvm_bytecode_builder_t* builder, uint8_t* byte, size_t* offset);
int vcvm_bytecode_builder_write_jmptable(vcvm_bytecode_builder_t* builder, uint8_t* byte, size_t* offset);

#ifdef __cplusplus
}
#endif  //__cplusplus


#endif
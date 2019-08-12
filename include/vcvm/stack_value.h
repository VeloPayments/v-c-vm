#ifndef VCVM_STACK_VALUE_HEADER_GUARD
#define VCVM_STACK_VALUE_HEADER_GUARD

#include <vpr/disposable.h>
#include <vpr/allocator.h>
#include <vcvm/stack_cert.h>

/* make this header C++ friendly. */
#ifdef __cplusplus
extern "C" {
#endif  //__cplusplus

typedef struct vcvm_stack_value
{
    disposable_t hdr;
    allocator_options_t* allocator_options;
    enum type
    {
        VCVM_STACK_VALUE_TYPE_STRING,
        VCVM_STACK_VALUE_TYPE_INTEGER,
        VCVM_STACK_VALUE_TYPE_UUID,
        VCVM_STACK_VALUE_TYPE_CERT
    } type;
    union
    {
        char* string;
        int32_t integer;
        uint8_t* uuid;
        vcvm_stack_cert_t* cert;
    };
} vcvm_stack_value_t;

int vcvm_stack_value_init(vcvm_stack_value_t* value, allocator_options_t* allocator_options);
int vcvm_stack_value_set_string(vcvm_stack_value_t* value, char* str);
int vcvm_stack_value_set_int(vcvm_stack_value_t* value, int32_t integer);
int vcvm_stack_value_set_uuid(vcvm_stack_value_t* value, uint8_t* uuid);
int vcvm_stack_value_set_cert(vcvm_stack_value_t* value, vcvm_stack_cert_t* cert);
int vcvm_stack_value_copy(vcvm_stack_value_t* dest, vcvm_stack_value_t* src);

#ifdef __cplusplus
}
#endif  //__cplusplus

#endif

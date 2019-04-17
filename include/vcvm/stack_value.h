#ifndef VCVM_STACK_VALUE_HEADER_GUARD
#define VCVM_STACK_VALUE_HEADER_GUARD

#include <vpr/disposable.h>
#include <vpr/allocator.h>

/* make this header C++ friendly. */
#ifdef __cplusplus
extern "C" {
#endif  //__cplusplus

typedef struct stack_value
{
    disposable_t hdr;
    allocator_options_t* allocator_options;
    enum type
    {
        STACK_VALUE_TYPE_STRING,
        STACK_VALUE_TYPE_INTEGER,
        STACK_VALUE_TYPE_UUID
    } type;
    union
    {
        char* string;
        int32_t integer;
        uint8_t* uuid;
    };
} stack_value_t;

int stack_value_init(stack_value_t* value, allocator_options_t* allocator_options);
int stack_value_set_string(stack_value_t* value, char* str);
int stack_value_set_int(stack_value_t* value, int32_t integer);
int stack_value_set_uuid(stack_value_t* value, uint8_t* uuid);
int stack_value_copy(stack_value_t* dest, stack_value_t* src);

#ifdef __cplusplus
}
#endif  //__cplusplus

#endif

#ifndef BUILD_VALUE_HEADER_GUARD
#    define BUILD_STACK_VALUE_HEADER_GUARD

/* make this header C++ friendly. */
#    ifdef __cplusplus
extern "C" {
#    endif  //__cplusplus

typedef struct stack_value
{
    enum type
    {
        STRING,
        INTEGER,
        UUID
    } type;
    union
    {
        char* string;
        uint32_t integer;
        uuid_t* uuid;
    };
} stack_value_t;

#    ifdef __cplusplus
}
#    endif  //__cplusplus

#endif

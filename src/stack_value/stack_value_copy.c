#include <vcvm/stack_value.h>
#include <vcvm/error_codes.h>

int stack_value_copy(stack_value_t* dest, stack_value_t* src)
{
    int result;
    switch (src->type)
    {
        case STACK_VALUE_TYPE_STRING:
            result = stack_value_set_string(dest, src->string);
            break;
        case STACK_VALUE_TYPE_INTEGER:
            result = stack_value_set_int(dest, src->integer);
            break;
        case STACK_VALUE_TYPE_UUID:
            result = stack_value_set_uuid(dest, src->uuid);
            break;
        default:
            result = VCVM_ERROR_STACK_VALUE_CANT_COPY;
    }
    return result;
}
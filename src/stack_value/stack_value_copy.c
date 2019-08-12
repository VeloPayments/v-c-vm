#include <vcvm/stack_value.h>
#include <vcvm/error_codes.h>

int vcvm_stack_value_copy(vcvm_stack_value_t* dest, vcvm_stack_value_t* src)
{
    int result;
    switch (src->type)
    {
        case VCVM_STACK_VALUE_TYPE_STRING:
            result = vcvm_stack_value_set_string(dest, src->string);
            break;
        case VCVM_STACK_VALUE_TYPE_INTEGER:
            result = vcvm_stack_value_set_int(dest, src->integer);
            break;
        case VCVM_STACK_VALUE_TYPE_UUID:
            result = vcvm_stack_value_set_uuid(dest, src->uuid);
            break;
        default:
            result = VCVM_ERROR_STACK_VALUE_CANT_COPY;
    }
    return result;
}
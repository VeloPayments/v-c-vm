#include <vcvm/stack_value.h>
#include <vcvm/error_codes.h>

int vcvm_stack_value_set_int(vcvm_stack_value_t* value, int32_t integer)
{
    value->type = VCVM_STACK_VALUE_TYPE_INTEGER;
    value->integer = integer;
    return VCVM_STATUS_SUCCESS;
}
#include <vcvm/stack_value.h>

void stack_value_set_int(stack_value_t* value, int32_t integer)
{
    value->type = STACK_VALUE_TYPE_INTEGER;
    value->integer = integer;
}
#include <vcvm/stack_value.h>
// See BLOC-208
#define __USE_XOPEN_EXTENDED true
#include <string.h>

void stack_value_set_string(stack_value_t* value, char* str)
{
    value->type = STACK_VALUE_TYPE_STRING;
    value->string = strdup(str);
}
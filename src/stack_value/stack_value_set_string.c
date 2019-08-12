#include <vcvm/stack_value.h>
// See BLOC-208
#define __USE_XOPEN_EXTENDED true
#include <string.h>
#include <vcvm/error_codes.h>

int vcvm_stack_value_set_string(vcvm_stack_value_t* value, char* str)
{
    value->type = VCVM_STACK_VALUE_TYPE_STRING;
    value->string = strdup(str);
    if (value->string == NULL)
    {
        return VCVM_ERROR_CANT_ALLOCATE;
    }
    return VCVM_STATUS_SUCCESS;
}
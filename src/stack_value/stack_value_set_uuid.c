#include <vcvm/stack_value.h>
#include <vcvm/error_codes.h>
#include <vcvm/size.h>
// See BLOC-208
#define __USE_XOPEN_EXTENDED true
#include <string.h>


int vcvm_stack_value_set_uuid(vcvm_stack_value_t* value, uint8_t* uuid)
{
    value->type = VCVM_STACK_VALUE_TYPE_STRING;
    value->uuid = (uint8_t*)allocate(value->allocator_options, UUID_SIZE);
    if (value->uuid == NULL)
    {
        return VCVM_ERROR_CANT_ALLOCATE;
    }

    memcpy(value->uuid, uuid, UUID_SIZE);
    return VCVM_STATUS_SUCCESS;
}
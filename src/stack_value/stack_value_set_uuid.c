#include <vcvm/stack_value.h>
// See BLOC-208
#define __USE_XOPEN_EXTENDED true
#include <string.h>

#define UUID_SIZE 16

void stack_value_set_uuid(stack_value_t* value, uint8_t* uuid)
{
    value->type = STACK_VALUE_TYPE_STRING;
    value->uuid = (uint8_t*) allocate(value->allocator_options, UUID_SIZE);
    memcpy(value->uuid, uuid, UUID_SIZE);
}
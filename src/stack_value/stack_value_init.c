#include <vcvm/stack_value.h>
#include <vcvm/error_codes.h>

static void stack_dispose(void* context);

int stack_value_init(stack_value_t* value, allocator_options_t* allocator_options)
{
    value->allocator_options = allocator_options;
    value->hdr.dispose = &stack_dispose;
    return VCVM_STATUS_SUCCESS;
}

void stack_dispose(void* ctx)
{
    stack_value_t* value = (stack_value_t*)ctx;
    switch (value->type)
    {
        case STACK_VALUE_TYPE_STRING:
            release(value->allocator_options, value->string);
            break;
        case STACK_VALUE_TYPE_UUID:
            release(value->allocator_options, value->uuid);
            break;
        default:
            // Don't care.
            break;
    }
}
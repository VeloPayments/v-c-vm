#include <vcvm/stack_cert.h>
#include <vcvm/error_codes.h>
#include <vpr/allocator.h>

static void stack_cert_dispose(void* ctx);

int stack_cert_init(stack_cert_t* cert, allocator_options_t* allocator_options, vccert_parser_options_t* parser_options)
{
    cert->allocator_options = allocator_options;
    cert->hdr.dispose = &stack_cert_dispose;
    cert->parser_options = parser_options;
    return VCVM_STATUS_SUCCESS;
}

void stack_cert_dispose(void* ctx)
{
    stack_cert_t* value = (stack_cert_t*)ctx;
    dispose((disposable_t*)value->parser_context);
    release(value->allocator_options, value->parser_context);
}
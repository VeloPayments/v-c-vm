#include <vcvm/stack_value.h>
#include <vcvm/error_codes.h>
#include <vcvm/stack_cert.h>

int stack_value_set_cert(stack_value_t* value, stack_cert_t* cert)
{
    value->type = STACK_VALUE_TYPE_CERT;
    value->cert = cert;
    return VCVM_STATUS_SUCCESS;
}
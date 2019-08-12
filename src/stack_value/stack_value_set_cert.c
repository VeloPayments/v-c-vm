#include <vcvm/stack_value.h>
#include <vcvm/error_codes.h>
#include <vcvm/stack_cert.h>

int vcvm_stack_value_set_cert(vcvm_stack_value_t* value, vcvm_stack_cert_t* cert)
{
    value->type = VCVM_STACK_VALUE_TYPE_CERT;
    value->cert = cert;
    return VCVM_STATUS_SUCCESS;
}
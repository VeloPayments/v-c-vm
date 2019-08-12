#include <vpr/disposable.h>
#include <vcvm/instruction.h>
#include <vcvm/error_codes.h>
#include <vpr/parameters.h>
#include <vcvm/stack_cert.h>
#include <vcvm/stack_value.h>
#include <include/vcvm/vm.h>

int vcvm_push_context_cert(vcvm_vm_t* vm)
{
    int result = VCVM_STATUS_SUCCESS;

    vcvm_stack_cert_t* cert = (vcvm_stack_cert_t*)allocate(vm->allocator_options, sizeof(vcvm_stack_cert_t));
    if (cert == NULL)
    {
        result = VCVM_ERROR_CANT_ALLOCATE;
        goto done;
    }

    vcvm_stack_value_t* value = (vcvm_stack_value_t*)allocate(vm->allocator_options, sizeof(vcvm_stack_value_t));
    if (value == NULL)
    {
        result = VCVM_ERROR_CANT_ALLOCATE;
        goto free_cert;
    }

    vcvm_stack_cert_init(cert, vm->allocator_options, vm->parser_options);
    vcvm_stack_value_init(value, vm->allocator_options);
    vcvm_stack_value_set_cert(value, cert);

    result = vcvm_vm_push(vm, value);
    goto done;

free_cert:
    release(vm->allocator_options, cert);
done:
    return result;
}

const vcvm_instruction_t VCVM_PUSH_CONTEXT_CERT = {
    .name = "PUSH_CONTEXT_CERT",
    .arity = 0,
    .handler = {
        .arity0 = &vcvm_push_context_cert,
    }
};
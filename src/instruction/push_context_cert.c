#include <vpr/disposable.h>
#include <vcvm/instruction.h>
#include <vcvm/error_codes.h>
#include <vpr/parameters.h>
#include <vcvm/stack_cert.h>
#include <vcvm/stack_value.h>
#include <include/vcvm/vm.h>

int push_context_cert(vm_t* vm)
{
    int result = VCVM_STATUS_SUCCESS;

    stack_cert_t* cert = (stack_cert_t*)allocate(vm->allocator_options, sizeof(stack_cert_t));
    if (cert == NULL)
    {
        result = VCVM_ERROR_CANT_ALLOCATE;
        goto done;
    }

    stack_value_t* value = (stack_value_t*)allocate(vm->allocator_options, sizeof(stack_value_t));
    if (value == NULL)
    {
        result = VCVM_ERROR_CANT_ALLOCATE;
        goto free_cert;
    }

    stack_cert_init(cert, vm->allocator_options, vm->parser_options);
    stack_value_init(value, vm->allocator_options);
    stack_value_set_cert(value, cert);

    result = vm_push(vm, value);
    goto done;

free_cert:
    release(vm->allocator_options, cert);
done:
    return result;
}

const instruction_t PUSH_CONTEXT_CERT = {
    .name = "PUSH_CONTEXT_CERT",
    .arity = 0,
    .handler = {
        .arity0 = &push_context_cert,
    }
};
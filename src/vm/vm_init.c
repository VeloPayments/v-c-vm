#include <vcvm/vm.h>
#include <vcvm/error_codes.h>
#include <vcvm/instruction.h>

static void vm_dispose(void* ctx);

int vm_init(vm_t* vm, allocator_options_t* allocator_options, bytecode_t* bytecode, uint8_t* context_cert)
{
    vm->hdr.dispose = &vm_dispose;
    vm->allocator_options = allocator_options;
    vm->sp = 0;
    vm->context_cert = context_cert;
    vm->bytecode = bytecode;
    return VCVM_STATUS_SUCCESS;
}

void vm_dispose(void* ctx)
{
    vm_t* vm = (vm_t*)ctx;
    dispose((disposable_t*)vm->bytecode);
    release(vm->allocator_options, vm);
}

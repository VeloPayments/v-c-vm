#include <vcvm/vm.h>
#include <vcvm/error_codes.h>
#include <vcvm/instruction.h>

static void vm_dispose(void* ctx);

int vm_init(vm_t* vm, allocator_options_t* allocator_options, vccert_parser_options_t* parser_options, uint8_t* context_cert, bytecode_t* bytecode)
{
    vm->hdr.dispose = &vm_dispose;
    vm->allocator_options = allocator_options;
    vm->parser_options = parser_options;
    vm->sp = 0;
    vm->context_cert = context_cert;
    vm->bytecode = bytecode;
    return VCVM_STATUS_SUCCESS;
}

void vm_dispose(void* ctx)
{
    vm_t* vm = (vm_t*)ctx;
    if (vm->bytecode != NULL)
    {
        dispose((disposable_t*)vm->bytecode);
    }
}

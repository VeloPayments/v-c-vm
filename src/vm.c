#include <vcvm/vm.h>
#include <vcvm/error_codes.h>
#include <vcvm/instruction.h>
#include <vcvm/opcode.h>

static void vm_dispose(void* ctx);

int vm_init(vm_t* vm, allocator_options_t* allocator_options, bytecode_t* bytecode)
{
    vm->hdr.dispose = &vm_dispose;
    vm->allocator_options = allocator_options;
    vm->sp = 0;
    vm->bytecode = bytecode;
    return VCVM_STATUS_SUCCESS;
}

void vm_dispose(void* ctx)
{
    vm_t* vm = (vm_t*)ctx;
    dispose((disposable_t*)vm->bytecode);
    release(vm->allocator_options, vm);
}

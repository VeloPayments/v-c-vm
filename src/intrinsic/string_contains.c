#include <vcvm/intrinsic.h>
#include <vcvm/vm.h>
#include <vcvm/stack_value.h>
#include <string.h>

const uint8_t STRING_CONTAINS_UUID[16] = {
    0x7D, 0x55, 0x2B, 0xCF, 0xE0, 0x8E, 0x4B, 0xAD, 0x92, 0xB2, 0x51, 0x11, 0x4B, 0x26, 0xA3, 0x40
};

int intrinsic_string_contains(vcvm_vm_t* vm)
{
    vcvm_stack_value_t* first;
    vcvm_vm_pop(vm, &first);

    vcvm_stack_value_t* second;
    vcvm_vm_pop(vm, &second);

    vcvm_stack_value_t* result = allocate(vm->allocator_options, sizeof(vcvm_stack_value_t));
    vcvm_stack_value_set_int(result, strstr(first->string, second->string) != NULL);

    vcvm_vm_push(vm, result);

    dispose((disposable_t*)first);
    release(vm->allocator_options, first);

    dispose((disposable_t*)second);
    release(vm->allocator_options, second);
    return 0;
}

const vcvm_intrinsic_t VCVM_STRING_CONTAINS = {
    .uuid = (uint8_t*)STRING_CONTAINS_UUID,
    .nargs = 2,
    .nrets = 1,
    .method = &intrinsic_string_contains
};

#include <vcvm/intrinsic.h>
#include <vpr/parameters.h>
#include <vcvm/vm.h>
#include <string.h>

const uint8_t STRING_CONTAINS_UUID[16] = {
    0x7D, 0x55, 0x2B, 0xCF, 0xE0, 0x8E, 0x4B, 0xAD, 0x92, 0xB2, 0x51, 0x11, 0x4B, 0x26, 0xA3, 0x40
};

int intrinsic_string_contains(vm_t* vm)
{
    stack_value_t* first;
    vm_pop(vm, &first);

    stack_value_t* second;
    vm_pop(vm, &second);

    stack_value_t* result = allocate(vm->allocator_options, sizeof(stack_value_t));
    stack_value_set_int(result, strstr(first->string, second->string) != NULL);

    vm_push(vm, result);

    dispose((disposable_t*)first);
    release(vm->allocator_options, first);

    dispose((disposable_t*)second);
    release(vm->allocator_options, second);
    return 0;
}

const intrinsic_t STRING_CONTAINS = {
    .uuid = (uint8_t*)STRING_CONTAINS_UUID,
    .nargs = 2,
    .nrets = 1,
    .method = &intrinsic_string_contains
};

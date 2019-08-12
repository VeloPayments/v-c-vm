#include <vcvm/intrinsic.h>
#include <vpr/parameters.h>

const uint8_t STRING_EQUALS_UUID[16] = {
    0xA0, 0xBC, 0x0A, 0xB6, 0xAF, 0x1A, 0x4A, 0x24, 0xB3, 0x72, 0x0D, 0xD6, 0xBD, 0x2C, 0x73, 0x0D
};

int intrinsic_string_equals(vcvm_vm_t* UNUSED(vm))
{
    return 0;
}

const vcvm_intrinsic_t VCVM_STRING_EQUALS = {
    .uuid = (uint8_t*)STRING_EQUALS_UUID,
    .nargs = 2,
    .nrets = 1,
    .method = &intrinsic_string_equals
};

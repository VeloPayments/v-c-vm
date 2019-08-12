#include <vcvm/intrinsic.h>
#include <vpr/parameters.h>

const uint8_t LOAD_ARTIFACT_UUID[16] = {
    0xB4, 0xE0, 0x68, 0xAC, 0x7E, 0xBB, 0x4A, 0xA3, 0xB2, 0x7F, 0x3B, 0x8C, 0x8B, 0x48, 0x97, 0xFC
};

int intrinsic_load_artifact(vcvm_vm_t* UNUSED(vm))
{
    return 0;
}

const vcvm_intrinsic_t VCVM_LOAD_ARTIFACT = {
    .uuid = (uint8_t*)LOAD_ARTIFACT_UUID,
    .nargs = 2,
    .nrets = 1,
    .method = &intrinsic_load_artifact
};

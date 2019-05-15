#include <vcvm/intrinsic.h>
#include <vpr/parameters.h>

const uint8_t LOAD_ARTIFACT_UUID[16] = {
    0xAF, 0xA3, 0xDE, 0xBA, 0x8C, 0x67, 0x4F, 0xDC, 0x9C, 0x14, 0xD, 0x87, 0x4B, 0x63, 0xF4, 0xDB
};

int intrinsic_load_artifact(vm_t* UNUSED(vm))
{
    return 0;
}

const intrinsic_t LOAD_ARTIFACT = {
    .uuid = (uint8_t*)LOAD_ARTIFACT_UUID,
    .nargs = 2,
    .nrets = 1,
    .method = &intrinsic_load_artifact
};

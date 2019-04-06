#include <vcvm/intrinsic.h>
#include <vcvm/error_codes.h>
#include <vpr/allocator.h>
#include <stdint.h>
#include <stdlib.h>

static void intrinsic_dispose(void* ctx);

int intrinsic_init(intrinsic_t* intrinsic, allocator_options_t* allocator_options, uint8_t* uuid, uint32_t nargs, uint32_t nrets)
{
    intrinsic->hdr.dispose = &intrinsic_dispose;
    intrinsic->allocator_options = allocator_options;
    intrinsic->uuid = uuid;
    intrinsic->nargs = nargs;
    intrinsic->nrets = nrets;

    return VCVM_STATUS_SUCCESS;
}

void intrinsic_dispose(void* ctx)
{
    intrinsic_t* intrinsic = (intrinsic_t*)ctx;
    free(intrinsic->uuid);
}

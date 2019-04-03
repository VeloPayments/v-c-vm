#include <vcvm/intrinsic.h>
#include <stdint.h>
#include <stdlib.h>

static void intrinsic_dispose(void *ctx);

int intrinsic_init(intrinsic_t *intrinsic, uuid_t *uuid, uint32_t nargs, uint32_t nrets, intrinsic_method_t method)
{
    intrinsic->hdr.dispose = &intrinsic_dispose;
    intrinsic->method = method;
    intrinsic->uuid = uuid;
    intrinsic->nargs = nargs;
    intrinsic->nrets = nrets;

    return 0;
}

void intrinsic_dispose(void *ctx)
{
    intrinsic_t *intrinsic = (intrinsic_t *) ctx;
    free(intrinsic->uuid);
}

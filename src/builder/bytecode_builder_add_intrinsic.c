#include <vpr/parameters.h>
#include <vcvm/builder.h>
#include <vpr/allocator.h>

#define UUID_SIZE 16

int bytecode_builder_add_intrinsic(bytecode_builder_t* builder, const intrinsic_t* intrinsic)
{
    intrinsic_constant_t* constant = hashmap_get(&builder->intrinsics, intrinsic->uuid, UUID_SIZE);
    if (constant != NULL)
    {
        return constant->index;
    }

    intrinsic_constant_t new_constant = {
        .index = builder->intrinsic_count++,
        .value = intrinsic
    };

    hashmap_put(&builder->intrinsics, intrinsic->uuid, UUID_SIZE, &new_constant);

    return new_constant.index;
}
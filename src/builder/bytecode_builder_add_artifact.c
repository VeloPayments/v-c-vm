#include <vpr/parameters.h>
#include <vcvm/builder.h>
#include <vpr/allocator.h>

#define UUID_SIZE 16

int bytecode_builder_add_artifact(bytecode_builder_t* builder, uint8_t* artifact_uuid)
{
    uuid_constant_t* constant = hashmap_get(&builder->artifacts, artifact_uuid, UUID_SIZE);
    if (constant != NULL)
    {
        return constant->index;
    }

    uuid_constant_t new_constant = {
        .index = builder->artifact_count++,
        .value = artifact_uuid
    };

    hashmap_put(&builder->artifacts, artifact_uuid, UUID_SIZE, &new_constant);

    return new_constant.index;
}
#include <vcvm/builder.h>
#include <vpr/allocator.h>

#define UUID_SIZE 16

int vcvm_bytecode_builder_add_uuid(vcvm_bytecode_builder_t* builder, uint8_t* uuid)
{
    vcvm_uuid_constant_t* constant = hashmap_get(&builder->uuids, uuid, UUID_SIZE);
    if (constant != NULL)
    {
        return constant->index;
    }

    vcvm_uuid_constant_t new_constant = {
        .index = builder->uuid_count++,
        .value = uuid
    };

    hashmap_put(&builder->uuids, uuid, UUID_SIZE, &new_constant);
    return new_constant.index;
}
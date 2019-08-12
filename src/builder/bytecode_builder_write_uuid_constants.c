#include <vcvm/builder.h>
#include <vpr/doubly_linked_list.h>
#include <string.h>
#include <vcvm/size.h>
#include <vcvm/error_codes.h>

int vcvm_bytecode_builder_write_uuid_constants(vcvm_bytecode_builder_t* builder, uint8_t* byte, size_t* offset)
{
    doubly_linked_list_t** buckets = (doubly_linked_list_t**)builder->uuids.buckets;
    size_t cap = builder->uuids.options->capacity;

    memcpy(byte + *offset, &builder->uuid_count, sizeof(uint32_t));
    *offset += sizeof(uint32_t);

    for (size_t i = 0; i < cap; i++)
    {
        doubly_linked_list_t* bucket = buckets[i];
        if (bucket == NULL)
        {
            continue;
        }

        doubly_linked_list_element_t* element = bucket->first;
        while (element != NULL)
        {
            hashmap_entry_t* entry = (hashmap_entry_t*)element->data;
            vcvm_uuid_constant_t* uuid = (vcvm_uuid_constant_t*)entry->val;
            memcpy(byte + *offset, uuid->value, UUID_SIZE);
            *offset += UUID_SIZE;
            element = element->next;
        }
    }

    return VCVM_STATUS_SUCCESS;
}
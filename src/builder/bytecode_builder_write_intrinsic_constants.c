#include <vcvm/builder.h>
#include <vpr/doubly_linked_list.h>
#include <vcvm/size.h>
#include <string.h>
#include <vcvm/error_codes.h>

int vcvm_bytecode_builder_write_intrinsic_constants(vcvm_bytecode_builder_t* builder, uint8_t* byte, size_t* offset)
{
    doubly_linked_list_t** buckets = (doubly_linked_list_t**)builder->intrinsics.buckets;
    size_t cap = builder->intrinsics.options->capacity;

    memcpy(byte + *offset, &builder->intrinsic_count, sizeof(uint32_t));
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
            vcvm_intrinsic_constant_t* intrinsic = (vcvm_intrinsic_constant_t*)entry->val;

            memcpy(byte + *offset, intrinsic->value->uuid, UUID_SIZE);
            *offset += UUID_SIZE;

            memcpy(byte + *offset, &intrinsic->value->nargs, sizeof(uint32_t));
            *offset += sizeof(uint32_t);

            memcpy(byte + *offset, &intrinsic->value->nrets, sizeof(uint32_t));
            *offset += sizeof(uint32_t);

            element = element->next;
        }
    }

    return VCVM_STATUS_SUCCESS;
}
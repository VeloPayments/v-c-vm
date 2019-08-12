#include <vcvm/builder.h>
#include <vcvm/error_codes.h>
#include <string.h>
#include <vpr/doubly_linked_list.h>

int vcvm_bytecode_builder_write_integer_constants(vcvm_bytecode_builder_t* builder, uint8_t* byte, size_t* offset)
{
    doubly_linked_list_t** buckets = (doubly_linked_list_t**)builder->integers.buckets;
    size_t cap = builder->integers.options->capacity;

    memcpy(byte + *offset, &builder->integer_count, sizeof(uint32_t));
    *offset += sizeof(uint32_t);

    if (builder->integer_count == 0)
    {
        return VCVM_STATUS_SUCCESS;
    }

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
            vcvm_integer_constant_t* number = (vcvm_integer_constant_t*)entry->val;
            memcpy(byte + *offset, &number->value, sizeof(int32_t));
            *offset += sizeof(int32_t);
            element = element->next;
        }
    }

    return VCVM_STATUS_SUCCESS;
}

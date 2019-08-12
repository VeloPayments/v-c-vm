#include <vcvm/builder.h>
#include <vcvm/error_codes.h>
#include <vpr/doubly_linked_list.h>
#include <string.h>

int vcvm_bytecode_builder_write_string_constants(vcvm_bytecode_builder_t* builder, uint8_t* byte, size_t* offset)
{
    doubly_linked_list_t** buckets = (doubly_linked_list_t**)builder->strings.buckets;
    size_t cap = builder->strings.options->capacity;

    memcpy(byte + *offset, &builder->string_count, sizeof(uint32_t));
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
            vcvm_string_constant_t* cstr = (vcvm_string_constant_t*)entry->val;

            size_t len = strlen(cstr->value);

            memcpy(byte + *offset, &len, sizeof(uint32_t));
            *offset += sizeof(uint32_t);

            memcpy(byte + *offset, cstr->value, len);
            *offset += len;

            element = element->next;
        }
    }

    return VCVM_STATUS_SUCCESS;
}
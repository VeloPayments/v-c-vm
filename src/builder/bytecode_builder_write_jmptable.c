#include <vcvm/builder.h>
#include <string.h>
#include <vcvm/error_codes.h>
#include <vpr/doubly_linked_list.h>

int bytecode_builder_write_jmptable(bytecode_builder_t* builder, uint8_t* byte, size_t* offset)
{
    doubly_linked_list_t** buckets = (doubly_linked_list_t**)builder->jmp_table.buckets;
    size_t cap = builder->jmp_table.options->capacity;

    memcpy(byte + *offset, &builder->jmp_count, sizeof(uint32_t));
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
            function_constant_t* func = (function_constant_t*) entry;

            memcpy(byte + *offset, &func->pc, sizeof(uint32_t));
            *offset += sizeof(uint32_t);

            element = element->next;
        }
    }

    return VCVM_STATUS_SUCCESS;
}
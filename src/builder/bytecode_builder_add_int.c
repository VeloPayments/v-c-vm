#include <vcvm/builder.h>
#include <stdint.h>
#include <vpr/parameters.h>
#include <string.h>

int bytecode_builder_add_int(bytecode_builder_t* builder, int32_t num)
{
    integer_constant_t* constant = hashmap_get64(&builder->integers, (uint64_t)num);
    if (constant != NULL)
    {
        return constant->index;
    }

    integer_constant_t new_constant = {
        .index = builder->integer_count++,
        .value = num,
    };

    hashmap_put64(&builder->integers, (uint64_t)num, &new_constant);

    return new_constant.index;
}
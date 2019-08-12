#include <vcvm/builder.h>
#include <stdint.h>
#include <string.h>

int vcvm_bytecode_builder_add_int(vcvm_bytecode_builder_t* builder, int32_t num)
{
    vcvm_integer_constant_t* constant = hashmap_get64(&builder->integers, (uint64_t)num);
    if (constant != NULL)
    {
        return constant->index;
    }

    vcvm_integer_constant_t new_constant = {
        .index = builder->integer_count++,
        .value = num,
    };

    hashmap_put64(&builder->integers, (uint64_t)num, &new_constant);

    return new_constant.index;
}
#include <vpr/parameters.h>
#include <vcvm/builder.h>
#include <vpr/allocator.h>
#include <vcvm/error_codes.h>
#include <vpr/hashmap.h>
#include <vpr/hash_func.h>
#include <string.h>

static void bytecode_builder_dispose(void* ctx);

static bool compare_string_constant(const void* x, const void* y);
static bool compare_uuid_constant(const void* x, const void* y);
static bool compare_intrinsic_constant(const void* x, const void* y);
static bool compare_int_constant(const void* x, const void* y);

int bytecode_builder_init(bytecode_builder_t* builder, allocator_options_t* allocator)
{
    builder->hdr.dispose = &bytecode_builder_dispose;
    builder->allocator_options = allocator;

    int result = hashmap_options_init(
        &builder->string_options,
        builder->allocator_options,
        MAX_CONSTANTS,
        &compare_string_constant,
        true,
        sizeof(string_constant_t),
        false);

    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    result = hashmap_options_init(
        &builder->integers_options,
        builder->allocator_options,
        MAX_CONSTANTS,
        &compare_int_constant,
        true,
        sizeof(integer_constant_t),
        false);

    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    result = hashmap_options_init(
        &builder->artifacts_options,
        builder->allocator_options,
        MAX_CONSTANTS,
        &compare_uuid_constant,
        true,
        sizeof(uuid_constant_t),
        false);

    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    result = hashmap_options_init(
        &builder->intrinsics_options,
        builder->allocator_options,
        MAX_CONSTANTS,
        &compare_intrinsic_constant,
        true,
        sizeof(intrinsic_constant_t),
        false);

    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    result = hashmap_init(&builder->string_options, &builder->strings);
    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    result = hashmap_init(&builder->integers_options, &builder->integers);
    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    result = hashmap_init(&builder->artifacts_options, &builder->artifacts);
    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    result = hashmap_init(&builder->intrinsics_options, &builder->intrinsics);
    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    result = dynamic_array_options_init(
        &builder->instructions_options,
        builder->allocator_options,
        sizeof(uint32_t),
        &compare_uint32);

    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    result = dynamic_array_init(&builder->instructions_options, &builder->instructions, MAX_INSTRUCTIONS, 0, NULL);

done:
    return result;
}

void bytecode_builder_dispose(void* ctx)
{
    bytecode_builder_t* builder = (bytecode_builder_t*)ctx;
    dispose((disposable_t*)&builder->string_options);
    dispose((disposable_t*)&builder->integers_options);
    dispose((disposable_t*)&builder->artifacts_options);
    dispose((disposable_t*)&builder->intrinsics_options);
    dispose((disposable_t*)&builder->strings);
    dispose((disposable_t*)&builder->integers);
    dispose((disposable_t*)&builder->artifacts);
    dispose((disposable_t*)&builder->intrinsics);
}

bool compare_int_constant(const void* x, const void* y)
{
    int a = *(int*)x;
    int b = *(int*)y;
    return a == b;
}

bool compare_intrinsic_constant(const void* x, const void* y)
{
    return x == y;
}

bool compare_uuid_constant(const void* x, const void* y)
{
    return memcmp(x, y, 16);
}

bool compare_string_constant(const void* x, const void* y)
{
    return strcmp((char*)x, (char*)y);
}
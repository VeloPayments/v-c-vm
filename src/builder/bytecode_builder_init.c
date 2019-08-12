#include <vcvm/builder.h>
#include <vpr/allocator.h>
#include <vcvm/error_codes.h>
#include <vpr/hashmap.h>
#include <vpr/hash_func.h>
#include <string.h>

#define UUID_SIZE 16

static void bytecode_builder_dispose(void* ctx);

static bool compare_string_constant(const void* x, const void* y);
static bool compare_uuid_constant(const void* x, const void* y);
static bool compare_intrinsic_constant(const void* x, const void* y);
static bool compare_int_constant(const void* x, const void* y);
static bool compare_function_constant(const void* x, const void* y);

static void dispose_function_constant(allocator_options_t* options, void* x);
static void dispose_string_constant(allocator_options_t* options, void* x);

static void simple_copy(void* destination, const void* source, size_t size);

int vcvm_bytecode_builder_init(vcvm_bytecode_builder_t* builder, allocator_options_t* allocator)
{
    builder->hdr.dispose = &bytecode_builder_dispose;
    builder->allocator_options = allocator;
    builder->string_size = 0;
    builder->string_count = 0;
    builder->integer_count = 0;
    builder->uuid_count = 0;
    builder->intrinsic_count = 0;
    builder->instruction_count = 0;
    builder->jmp_count = 0;

    int result = hashmap_options_init_ex(
        &builder->string_options,
        builder->allocator_options,
        MAX_CONSTANTS,
        &sdbm,
        &compare_string_constant,
        &simple_copy,
        sizeof(vcvm_string_constant_t),
        &dispose_string_constant);

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
        sizeof(vcvm_integer_constant_t),
        true);

    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    result = hashmap_options_init(
        &builder->uuid_options,
        builder->allocator_options,
        MAX_CONSTANTS,
        &compare_uuid_constant,
        true,
        sizeof(vcvm_uuid_constant_t),
        true);

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
        sizeof(vcvm_intrinsic_constant_t),
        true);

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

    result = hashmap_init(&builder->uuid_options, &builder->uuids);
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

    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    result = hashmap_options_init_ex(
        &builder->jmp_options,
        builder->allocator_options,
        MAX_JMPS,
        &sdbm,
        &compare_function_constant,
        &simple_copy,
        sizeof(vcvm_function_constant_t),
        &dispose_function_constant);

    if (result != VCVM_STATUS_SUCCESS)
    {
        goto done;
    }

    result = hashmap_init(&builder->jmp_options, &builder->jmp_table);

done:
    return result;
}

void bytecode_builder_dispose(void* ctx)
{
    vcvm_bytecode_builder_t* builder = (vcvm_bytecode_builder_t*)ctx;

    // I didn't intend for this text to cascade.
    dispose((disposable_t*)&builder->strings);
    dispose((disposable_t*)&builder->integers);
    dispose((disposable_t*)&builder->uuids);
    dispose((disposable_t*)&builder->intrinsics);
    dispose((disposable_t*)&builder->instructions);
    dispose((disposable_t*)&builder->jmp_table);
    dispose((disposable_t*)&builder->string_options);
    dispose((disposable_t*)&builder->integers_options);
    dispose((disposable_t*)&builder->uuid_options);
    dispose((disposable_t*)&builder->intrinsics_options);
    dispose((disposable_t*)&builder->instructions_options);
    dispose((disposable_t*)&builder->jmp_options);
}

void dispose_string_constant(allocator_options_t* options, void* x)
{
    // See BLOC-233 as to why im using free directly.
    vcvm_string_constant_t* string_constant = (vcvm_string_constant_t*)x;
    free(string_constant->value);

    release(options, x);
}

void dispose_function_constant(allocator_options_t* options, void* x)
{
    // See BLOC-233 as to why im using free directly.
    vcvm_function_constant_t* func_constant = (vcvm_function_constant_t*)x;
    free(func_constant->value);

    release(options, x);
}

void simple_copy(void* destination, const void* source, size_t size)
{
    memcpy(destination, source, size);
}

bool compare_function_constant(const void* x, const void* y)
{
    vcvm_function_constant_t* right = (vcvm_function_constant_t*)y;
    return strcmp(right->value, (char*)x) == 0;
}

bool compare_int_constant(const void* x, const void* y)
{
    vcvm_integer_constant_t* right = (vcvm_integer_constant_t*)y;
    int32_t left = *(int32_t*)x;
    return right->value == left;
}

bool compare_intrinsic_constant(const void* x, const void* y)
{
    vcvm_intrinsic_constant_t* right = (vcvm_intrinsic_constant_t*)y;
    uint8_t* left = (uint8_t*)x;
    return memcmp(right->value->uuid, left, UUID_SIZE) == 0;
}

bool compare_uuid_constant(const void* x, const void* y)
{
    vcvm_uuid_constant_t* right = (vcvm_uuid_constant_t*)y;
    uint8_t* left = (uint8_t*)x;
    return memcmp(right->value, left, UUID_SIZE) == 0;
}

bool compare_string_constant(const void* x, const void* y)
{
    vcvm_string_constant_t* right = (vcvm_string_constant_t*)y;
    return strcmp(right->value, (char*)x) == 0;
}

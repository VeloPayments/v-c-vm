#include <minunit/minunit.h>
#include <vpr/allocator.h>
#include <vpr/disposable.h>
#include <vpr/allocator/malloc_allocator.h>
#include <vcvm/vm.h>
#include <vcvm/error_codes.h>

TEST_SUITE(builder);

TEST(instruction_subtract)
{
    allocator_options_t options;
    malloc_allocator_options_init(&options);

    vm_t vm;
    vm_init(&vm, &options, NULL, NULL);

    auto first = (stack_value_t*)allocate(&options, sizeof(stack_value_t));
    TEST_ASSERT(first != nullptr);
    auto second = (stack_value_t*)allocate(&options, sizeof(stack_value_t));
    TEST_ASSERT(second != nullptr);

    int result = stack_value_init(first, &options);
    TEST_ASSERT(result == VCVM_STATUS_SUCCESS);

    result = stack_value_init(second, &options);
    TEST_ASSERT(result == VCVM_STATUS_SUCCESS);

    stack_value_set_int(first, 6);
    stack_value_set_int(second, 5);

    result = vm_push(&vm, first);
    TEST_ASSERT(result == VCVM_STATUS_SUCCESS);

    result = vm_push(&vm, second);
    TEST_ASSERT(result == VCVM_STATUS_SUCCESS);

    result = subtract(&vm);
    TEST_EXPECT(result == VCVM_STATUS_SUCCESS);

    stack_value_t* value;
    result = vm_pop(&vm, &value);
    TEST_EXPECT(result == VCVM_STATUS_SUCCESS);

    TEST_EXPECT(value->integer == 1);

    dispose((disposable_t*)value);
    release(&options, value);

    dispose((disposable_t*)&vm);
    dispose((disposable_t*)&options);
}

TEST(instruction_add)
{
    allocator_options_t options;
    malloc_allocator_options_init(&options);

    vm_t vm;
    vm_init(&vm, &options, NULL, NULL);

    auto first = (stack_value_t*)allocate(&options, sizeof(stack_value_t));
    TEST_ASSERT(first != nullptr);
    auto second = (stack_value_t*)allocate(&options, sizeof(stack_value_t));
    TEST_ASSERT(second != nullptr);

    int result = stack_value_init(first, &options);
    TEST_ASSERT(result == VCVM_STATUS_SUCCESS);

    result = stack_value_init(second, &options);
    TEST_ASSERT(result == VCVM_STATUS_SUCCESS);

    stack_value_set_int(first, 5);
    stack_value_set_int(second, 6);

    result = vm_push(&vm, first);
    TEST_ASSERT(result == VCVM_STATUS_SUCCESS);

    result = vm_push(&vm, second);
    TEST_ASSERT(result == VCVM_STATUS_SUCCESS);

    result = add(&vm);
    TEST_EXPECT(result == VCVM_STATUS_SUCCESS);

    stack_value_t* value;
    result = vm_pop(&vm, &value);
    TEST_EXPECT(result == VCVM_STATUS_SUCCESS);

    TEST_EXPECT(value->integer == 11);

    dispose((disposable_t*)value);
    release(&options, value);

    dispose((disposable_t*)&vm);
    dispose((disposable_t*)&options);
}
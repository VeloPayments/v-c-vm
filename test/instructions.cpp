#include <minunit/minunit.h>
#include <vpr/allocator.h>
#include <vpr/disposable.h>
#include <vpr/allocator/malloc_allocator.h>
#include <vcvm/vm.h>
#include <vcvm/error_codes.h>

TEST_SUITE(builder);

TEST(instruction_subtract)
{
    allocator_options_t allocator_options;
    malloc_allocator_options_init(&allocator_options);

    vcvm_vm_t vm;
    vcvm_vm_init(&vm, &allocator_options, nullptr, nullptr, nullptr);

    auto first = (vcvm_stack_value_t*)allocate(&allocator_options, sizeof(vcvm_stack_value_t));
    TEST_ASSERT(first != nullptr);
    auto second = (vcvm_stack_value_t*)allocate(&allocator_options, sizeof(vcvm_stack_value_t));
    TEST_ASSERT(second != nullptr);

    int result = vcvm_stack_value_init(first, &allocator_options);
    TEST_ASSERT(result == VCVM_STATUS_SUCCESS);

    result = vcvm_stack_value_init(second, &allocator_options);
    TEST_ASSERT(result == VCVM_STATUS_SUCCESS);

    vcvm_stack_value_set_int(first, 6);
    vcvm_stack_value_set_int(second, 5);

    result = vcvm_vm_push(&vm, first);
    TEST_ASSERT(result == VCVM_STATUS_SUCCESS);

    result = vcvm_vm_push(&vm, second);
    TEST_ASSERT(result == VCVM_STATUS_SUCCESS);

    result = vcvm_subtract(&vm);
    TEST_EXPECT(result == VCVM_STATUS_SUCCESS);

    vcvm_stack_value_t* value;
    result = vcvm_vm_pop(&vm, &value);
    TEST_EXPECT(result == VCVM_STATUS_SUCCESS);

    TEST_EXPECT(value->integer == 1);

    dispose((disposable_t*)value);
    release(&allocator_options, value);

    dispose((disposable_t*)&vm);
    dispose((disposable_t*)&allocator_options);
}

TEST(instruction_add)
{
    allocator_options_t allocator_options;
    malloc_allocator_options_init(&allocator_options);

    vcvm_vm_t vm;
    vcvm_vm_init(&vm, &allocator_options, nullptr, nullptr, nullptr);

    auto first = (vcvm_stack_value_t*)allocate(&allocator_options, sizeof(vcvm_stack_value_t));
    TEST_ASSERT(first != nullptr);
    auto second = (vcvm_stack_value_t*)allocate(&allocator_options, sizeof(vcvm_stack_value_t));
    TEST_ASSERT(second != nullptr);

    int result = vcvm_stack_value_init(first, &allocator_options);
    TEST_ASSERT(result == VCVM_STATUS_SUCCESS);

    result = vcvm_stack_value_init(second, &allocator_options);
    TEST_ASSERT(result == VCVM_STATUS_SUCCESS);

    vcvm_stack_value_set_int(first, 5);
    vcvm_stack_value_set_int(second, 6);

    result = vcvm_vm_push(&vm, first);
    TEST_ASSERT(result == VCVM_STATUS_SUCCESS);

    result = vcvm_vm_push(&vm, second);
    TEST_ASSERT(result == VCVM_STATUS_SUCCESS);

    result = vcvm_add(&vm);
    TEST_EXPECT(result == VCVM_STATUS_SUCCESS);

    vcvm_stack_value_t* value;
    result = vcvm_vm_pop(&vm, &value);
    TEST_EXPECT(result == VCVM_STATUS_SUCCESS);

    TEST_EXPECT(value->integer == 11);

    dispose((disposable_t*)value);
    release(&allocator_options, value);

    dispose((disposable_t*)&vm);
    dispose((disposable_t*)&allocator_options);
}
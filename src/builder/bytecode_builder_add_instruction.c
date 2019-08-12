#include <vcvm/builder.h>
#include <vpr/allocator.h>
#include <vpr/dynamic_array.h>
#include <vcvm/error_codes.h>

int vcvm_bytecode_builder_add_instruction(vcvm_bytecode_builder_t* builder, uint32_t instruction)
{
    builder->instruction_count++;
    int result = dynamic_array_append(&builder->instructions, &instruction);
    return result != VPR_STATUS_SUCCESS ? result : VCVM_STATUS_SUCCESS;
}
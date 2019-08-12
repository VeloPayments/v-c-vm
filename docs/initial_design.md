# Initial Design

Initial design document

## Goals

- First pass at a working schema VM
- First pass at instructions
- First pass at vcvm_bytecode format

## Bytecode format

All vcvm_bytecode will have the following format for this version (rough C)

```c
typedef struct vcvm_bytecode {
    uint32_t magic_number; // Should be 0xDECAF.
    uint32_t string_const_count;
    char* string_consts[string_const_count];
    uint32_t uuid_const_count;
    uint8_t* uuid_consts[uuid_const_count];
    uint32_t int_const_count;
    uint32_t* int_consts[int_const_count];
    uint32_t intrinsic_const_count;
    vcvm_intrinsic_t intrinsic_consts[intrinsic_const_count];
    uint32_t instruction_count;
    uint32_t instructions[instruction_count];
} vcvm_bytecode_t;
```
For this version the magic number will be `0xDECAF`.
The content of the structure is not guaranteed to be backwards compatible yet.

## Instruction format

The vcvm_instruction format will depend on the number of operands.
If there are three operands then the format is as follows;

|    0 - 7    | 8 - 15 | 16 - 23 | 24 - 31 |
|-------------|--------|---------|---------|
| vcvm_instruction | A      | B       | C       |

If there are two arguments then it will be

|    0 - 7    | 8 - 19 | 20 - 31 |
|-------------|--------|---------|
| vcvm_instruction | A      | B       |


And just one argument (maybe empty) will be

|    0 - 7    | 8 - 31 |
|-------------|--------|
| vcvm_instruction | A      |


## Opcodes

| Name  | Opcode | Arguments |        Effect         |
|-------|--------|-----------|-----------------------|
| Halt  | 0x0    |           | Halt                  |
| Pop   | 0x1    |           | Pop TOS               |
| Push  | 0x2    | A         | Push intermediate A   |
| Swap  | 0x3    |           | Swap top two elements |
| Calli | 0x4    | A         | Call the vcvm_intrinsic[A] |
| LoadK | 0x5    | A         | Load const[A] to TOS  |

## Intrinsics

Intrinsics are a way to support arbitrary built in functions. Rather than making the Opcodes a mess
we can simply support any number of functions by exposing well known references. To keep things deterministic 
an vcvm_intrinsic will be referenced by a STACK_VALUE_TYPE_UUID, this STACK_VALUE_TYPE_UUID gives it a deterministic name and version binding. We can
bind multiple methods of the same action to different UUIDs and let the user decide what method they bind against.

(Python pseudo code)
```python
{
    "e0a520a3-bcfe-44c8-bf1e-291adb500221": int_in_range,
    "a4c39daa-f85e-4b2a-a37f-4914e8237a18": string_contains,
    # ...
}
```

In the vcvm_bytecode there will be a pool of intrinsics that contain the following information

```c
typedef struct vcvm_intrinsic {
    uint8_t* uuid;
    int nargs;
    int nrets;
    char* name; // Possible debug info.
} vcvm_intrinsic_t;
```
In the future this will be extended to support type information on arguments allowing for stricter matching.

When the virtual machine loads some vcvm_bytecode it will scan the vcvm_intrinsic pool and see if it can match the vcvm_intrinsic requested
to loaded methods. First it will check if there is an vcvm_intrinsic loaded for a given STACK_VALUE_TYPE_UUID. It will then compare `nargs` and `nrets`
if they match then this is enough for us to load that into the vm for use during execution.

In vcvm_bytecode an vcvm_intrinsic might work like so (just a pseudo example)

```
.consts = ["test", "testing"]
.instrinsics = [{"a4c39daa-f85e-4b2a-a37f-4914e8237a18": {"nargs": 2, "nrets": 1}}]

LOADK 1
LOADK 0
CALLI 0
```

This example would load `"testing"` then load `"test"` then call the first vcvm_intrinsic, which in this example is `string_contains`
This would leave `True` on the stack.

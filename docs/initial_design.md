# Initial Design

Initial design document

## Goals

- First pass at a working schema VM
- First pass at instructions
- First pass at bytecode format

## Bytecode format

All bytecode will have the following format for this version (rough C)

```c
typedef struct bytecode {
    uint32_t magic_number; // Should be 0xDECAF.
    uint32_t string_const_count;
    char* string_consts[string_const_count];
    uint32_t uuid_const_count;
    uint8_t* uuid_consts[uuid_const_count];
    uint32_t int_const_count;
    uint32_t* int_consts[int_const_count];
    uint32_t intrinsic_const_count;
    intrinsic_t intrinsic_consts[intrinsic_const_count];
    uint32_t instruction_count;
    uint32_t instructions[instruction_count];
} bytecode_t;
```
For this version the magic number will be `0xDECAF`.
The content of the structure is not garanteed to be backwards compatible yet.

## Instruction format

The instruction format will depend on the number of operands.
If there are three operands then the format is as follows;

|    0 - 7    | 8 - 15 | 16 - 23 | 24 - 31 |
|-------------|--------|---------|---------|
| instruction | A      | B       | C       |

If there are two arguments then it will be

|    0 - 7    | 8 - 19 | 20 - 31 |
|-------------|--------|---------|
| instruction | A      | B       |


And just one argument (maybe empty) will be

|    0 - 7    | 8 - 31 |
|-------------|--------|
| instruction | A      |


## Opcodes

| Name  | Opcode | Arguments |        Effect         |
|-------|--------|-----------|-----------------------|
| Halt  | 0x0    |           | Halt                  |
| Pop   | 0x1    |           | Pop TOS               |
| Push  | 0x2    | A         | Push const[A]         |
| Swap  | 0x3    |           | Swap top two elements |
| Calli | 0x4    | A         | Call the intrinsic[A] |
| LoadK | 0x5    | A         | Load const[A] to TOS  |

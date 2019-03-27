# Initial Design

Initial design document

## Goals

- First pass at a working schema VM
- First pass at instructions
- First pass at bytecode format

## Bytecode format

All bytecode will have the following format for this version (pseudo C)

```c
struct bytecode {
    uint_32 magic_number;
    uint_32 count;
    uint_32 instructions[count];
}
```
For this version the magic number will be `0x64756d62`.
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

PUSH(A) - Push intermedate value A onto the stack
POP - Pop the top of the stack
### TODO

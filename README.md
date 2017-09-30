# [C]HIP-8
A CHIP-8 emulator written in C. Interested in emulation, I found that this system 
is a good starter project for those interested in developing emulators, due to its 
simple design and small number of opcodes to implement.

## Running this project
Download the code and compile it with `make`.

Usage: `./chip8 <game_file>`
- `<game_file>`: relative path to an assembled CHIP-8 game

## Opcode table
Taken from [Wikipedia](https://en.wikipedia.org/wiki/CHIP-8).

| Implemented | Opcode | Operation | Explanation |
|-------------|--------|-----------|-------------|
| ✓ | 0NNN | | Calls RCA 1802 program at address NNN. Not necessary for most ROMs. |
| ✓ | 00E0 | `disp_clear()` | Clears the screen. |
| ✓ | 00EE | `return;` | Returns from a subroutine. |
| ✓ | 1NNN | `goto NNN;` | Jumps to address NNN. |
| ✓ | 2NNN | `*(0xNNN)()` | Calls subroutine at NNN. |
|  | 3XNN | `if (VX == NN)` | Skips the next instruction if VX equals NN. (Usually the next instruction is a jump to skip a code block) |
|  | 4XNN | `if (VX != NN)` | Skips the next instruction if VX doesn't equal NN. (Usually the next instruction is a jump to skip a code block) |
|  | 5XY0 | `if (VX == VY)` | Skips the next instruction if VX equals VY. (Usually the next instruction is a jump to skip a code block) |
|  | 6XNN | `VX = NN` | Sets VX to NN. |
|  | 7XNN | `VX += NN` | Adds NN to VX. (Carry flag is not changed) |
|  | 8XY0 | `VX = VY` | Sets VX to the value of VY. |
|  | 8XY1 | `VX = VX \| VY` | Sets VX to VX or VY. (Bitwise OR operation) |
|  | 8XY2 | `VX = VX & VY` | Sets VX to VX and VY. (Bitwise AND operation) |
|  | 8XY3 | `VX = VX ^ VY` | Sets VX to VX xor VY. |
|  | 8XY4 | `VX += VY` | Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't. |
|  | 8XY5 | `VX -= VY` | VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't. |
|  | 8XY6 | `VX = VY = VY >> 1` | Shifts VY right by one and copies the result to VX. VF is set to the value of the least significant bit of VY before the shift. |
|  | 8XY7 | `VX = VY - VX` | Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't. |
|  | 8XYE | `VX = VY = VY << 1` | Shifts VY left by one and copies the result to VX. VF is set to the value of the most significant bit of VY before the shift. |
|  | 9XY0 | `if (VX != VY)` | Skips the next instruction if VX doesn't equal VY. (Usually the next instruction is a jump to skip a code block) |
|  | ANNN | `I = NNN` | Sets I to the address NNN. |
|  | BNNN | `PC = V0 + NNN` | Jumps to the address NNN plus V0. |
|  | CXNN | `VX = rand() & NN` | Sets VX to the result of a bitwise and operation on a random number (Typically: 0 to 255) and NN. |
|  | DXYN | `draw(VX, VY, N)` | Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N pixels. Each row of 8 pixels is read as bit-coded starting from memory location I; I value doesn’t change after the execution of this instruction. As described above, VF is set to 1 if any screen pixels are flipped from set to unset when the sprite is drawn, and to 0 if that doesn’t happen |
|  | EX9E | `if (key() == VX)` | Skips the next instruction if the key stored in VX is pressed. (Usually the next instruction is a jump to skip a code block) |
|  | EXA1 | `if (key() != VX)` | Skips the next instruction if the key stored in VX isn't pressed. (Usually the next instruction is a jump to skip a code block) |
|  | FX07 | `VX = get_delay()` | Sets VX to the value of the delay timer. |
|  | FX0A | `VX = get_key()` | A key press is awaited, and then stored in VX. (Blocking Operation. All instruction halted until next key event) |
|  | FX15 | `delay_timer(VX)` | Sets the delay timer to VX. |
|  | FX18 | `sound_timer(VX)` | Sets the sound timer to VX. |
|  | FX1E | `I += VX` | Adds VX to I.[3] |
|  | FX29 | `I = sprite_addr[VX]` | Sets I to the location of the sprite for the character in VX. Characters 0-F (in hexadecimal) are represented by a 4x5 font. |
|  | FX33 | `set_BCD(VX);`<br>`*(I+0) = BCD(3);`<br>`*(I+1) = BCD(2);`<br>`*(I+2) = BCD(1);` | Stores the binary-coded decimal representation of VX, with the most significant of three digits at the address in I, the middle digit at I plus 1, and the least significant digit at I plus 2. (In other words, take the decimal representation of VX, place the hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2.) |
|  | FX55 | `reg_dump(VX, &I)` | Stores V0 to VX (including VX) in memory starting at address I. I is increased by 1 for each value written. |
|  | FX65 | `reg_load(VX, &I)` | Fills V0 to VX (including VX) with values from memory starting at address I. I is increased by 1 for each value written. |

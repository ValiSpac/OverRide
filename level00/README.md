# Level 00

First level will wait for a password input with the `scanf()` function.
If it is not equil to 5276 (as decimal number) it will be an invalid password.

So we just type in 5276 to `scanf()` and we are good to go!

```
08048494    {
08048494        puts("***********************************");
080484b0        puts("* \t     -Level00 -\t\t  *");
080484bc        puts("***********************************");
080484c9        printf("Password:");
080484de        int32_t var_14;
080484de        __isoc99_scanf(0x8048636, &var_14);
080484de
080484ec        if (var_14 != 0x149c) # Dec: 5276
080484ec        {
08048514            puts("\nInvalid Password!");
08048519            return 1;
080484ec        }
080484ec
080484f5        puts("\nAuthenticated!");
08048501        system("/bin/sh");
08048506        return 0;
08048494    }
```

```
level00@OverRide:~$ ./level00 
***********************************
*       -Level00 -    *
***********************************
Password:5276

Authenticated!
$ cat /home/users/level01/.pass
uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL
```

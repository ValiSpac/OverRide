We can see that there are multiple protections in the program, ptrace protection so we can't have another trace of the program and run a debugger on it a stack protector for buffer overflows.
Considering the code, it will apply a checksum loop on the auth and derive the password from that. 
To be able to analyze a generated password first we can overwrite the return value of ptrace to only be 0.
Second we will place a breakpoint before the check to analyze the expected serial number
```
(gdb) b *0x080487ba
Breakpoint 1 at 0x80487ba
(gdb) b *0x08048866
Breakpoint 2 at 0x8048866
(gdb) r
Starting program: /home/users/level06/level06 
***********************************
*		level06		  *
***********************************
-> Enter Login: vpac06
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 123123123

Breakpoint 1, 0x080487ba in auth ()
(gdb) set $eax=0
(gdb) next
Single stepping until exit from function auth,
which has no line number information.

Breakpoint 2, 0x08048866 in auth ()
(gdb) x/wx $ebp-0x10
0xffffd5b8:	0x005f1b24
(gdb) p /d 0x005f1b24
$1 = 6232868
```

```
level06@OverRide:~$ ./level06 
***********************************
*		level06		  *
***********************************
-> Enter Login: vpac06
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6232868
Authenticated!
$ whoami
level07
$ cat /home/users/level07/.pass
GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8
```
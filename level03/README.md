# Level 03

First we can see in our program that our input will be subtracted from 322424845. If the diference is smaller than 21, it will execute `n` amount of times and if it is bigger it will execute `rand()` amount of times. So we have to find the certain value that can encrypt "Congratulations!" to "Q}|u\`sfg~sf{}|a3" based on the `asm` analysis.

We will use this script to check:
```c
str_encrypt = "Congratulations!"
str_decrypt = "Q}|u`sfg~sf{}|a3"
counter = 21

while counter != 0:
    tmp = ''.join(chr(ord(c) ^ counter) for c in str_encrypt)
    if tmp == str_decrypt:
        print("Found it, it is : {}".format(counter))
        break
    counter -= 1
```

Now we only need to get our value and subtract it from 322424845

```c
level03@OverRide:~$ python /tmp/scrip.py 
Found it, it is : 18
level03@OverRide:~$ ./level03 
***********************************
*		level03		**
***********************************
Password:322424827
$ whoami
level04
$ cat /home/users/level04/.pass
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
```

#include <sys/ptrace.h>
#include <string.h>
#include <stdio.h>

int auth(int serial, char *buf)
{
    buf[strcspn(buf, "\n")] = '\0';

    int len = strnlen(buf, 32);
    if (len <= 5)
        return 1;

    if (ptrace(PTRACE_TRACEME, 0, 1, 0) == -1) {
        puts("\033[32m.---------------------------.");
        puts("\033[31m| !! TAMPERING DETECTED !!  |");
        puts("\033[32m.---------------------------.");
        return 1;
    }

    int acc = (int)(buf[3]) ^ 0x1337;
    acc += 0x5eeded;

    for (int i = 0; i < len; i++) {
        if ((unsigned char)buf[i] <= 0x1f)
            return 1;

        int xored   = (int)(buf[i]) ^ acc;
        acc        += xored % 1337;
    }

    if (serial == acc)
        return 0;

    return 1;
}

int main()
{
    char buf[32];
    int serial;

    unsigned int canary;
    unsigned int ret;
    __asm__ ("movl %%gs:0x14, %0" : "=r" (canary));
    ret = canary;

    puts("***********************************");
    puts("*\t\tlevel06\t\t  *");
    puts("***********************************");
    printf("-> Enter Login: ");

    fgets( 1, 32, buf);

    puts("***********************************");
    puts("***** NEW ACCOUNT DETECTED ********");
    puts("***********************************");
    printf("-> Enter Serial: ");

    scanf("%u", serial);
    if (auth(serial, buf) == 0){
        puts("Authenticated!");
        system("/bin/sh");
    }

    __asm__ ("movl %%gs:0x14, %0" : "=r" (canary));
    if (ret != canary)
        __stack_check_failed();
    return 0;
}

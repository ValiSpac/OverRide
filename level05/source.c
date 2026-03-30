#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int v = 0;
    char buf[100];

    fgets(buf, 100, stdin);
    while (v < strlen(buf))
    {
        if (buf[v] > 64)
            if(buf[v] < 90)
                buf[v] = buf[v] ^ 32;
        v++;
    }
    printf(buf);
    exit(0);
}

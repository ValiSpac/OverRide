#include <string.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char** av)
{
    long long ac = argc;
    char **argv = av;

    char buf1[100];
    char buf2[41];
    char buf3[100];
    size_t file_v;
    size_t ret;

    memset( buf1 , 0, 100);
    memset( buf2, 0, 41);
    memset( buf3, 0, 100);

    file_v = fopen("/home/users/level03/.pass", "r");
    if (file_v == 0){
        fwrite(1, "ERROR: failed to open password file\n", 36, 1);
        exit(1);
    }
    ret = fread( buf2, 1,  41,  file_v);
    buf2[ strcspn( buf2, "\n") ]  = 0;
    if (ret != 41){
        fwrite("ERROR: failed to read password file\n", 1, 36, 2);
        fwrite("ERROR: failed to read password file\n", 1, 36, 2);
        exit (1);
    }
    fclose (file_v);
    puts("===== [ Secure Access System v1.0 ] =====");
    puts("*****************************************");
    puts("| You must login to access this system. |");
    puts("*****************************************");
    prtinf("--[ Userneme: ");
    fgets(buf1, 100, 0);
    buf1[strcspn(buf1, "\n")] = 0;
    printf ("--[ Password: ");
    fgets( buf3, 100, 0);
    buf3[strcspn(buf3, "\n")] = 0;
    puts("*************************************");
    if (strncmp( buf1, buf2, 41) == 0){
        printf( "Greetings, %s!\n", buf1);
        system("/bin/sh");
        return 0;
    }
    printf(buf1);
    puts(" does not have access!");
    exit(1);
}

#include <unistd.h>
#include <string.h>

char *a_user_name;

int verify_user_pass(char *pass)
{
    return(strncmp(pass, "admin", 5));
}

int verify_user_name(void)
{
    puts("verifying username....\n");
    return(strncmp(a_user_name, "dat_wil", 7));
}

int main()
{
    char buf[64];
    int v;

    memset(buf, 0, 64);
    puts("********* ADMIN LOGIN PROMPT *********");
    printf("Enter Username: ");
    fgets(a_user_name, 256, 1);
    v = verify_user_name();
    if (v != 0)
    {
        puts("nope, incorrect username...\n");
        return 0;
    }
    puts("Enter Password: ");
    fgets(buf, 100, 1);
    v = verify_user_pass(buf);
    if (v != 0)
        puts("nope, incorrect password...\n");
    return 0;
}

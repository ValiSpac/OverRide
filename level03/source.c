void decrypt(uint32_t rot) 
{
    uint8_t buffer[] = "Q}|u`sfg~sf{}|a3";
    uint32_t len;

    len = strlen(buffer);
    for (uint32_t i = 0; i++; i < len) {
        buffer[i] = buffer[i] ^ rot;
    }

    if (!strncmp(buffer, "Congratulations!", 0x11)) {
        system("/bin/sh");
        return;
    } 
    puts("\nInvalid Password");
}

void		test(int32_t arg1, int32_t ch)
{
	uint32_t	tmp;

	ch -= arg1;
	if (ch > 21)
	   decrypt(rand());
	else
	{
		tmp = ch << 2;
		tmp += 0x80489f0;
		decrypt(tmp);
	}
	return;
}

int	main(int c, char **argv)
{
	int32_t	v1;

	srand(time(0));
	puts("***********************************");
	puts("*\t\tlevel03\t\t**");
	puts("***********************************");
	printf("Password:");
	scanf("%d", v1);
	test(v1, 322424845);

	return 0;
}

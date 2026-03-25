#include <stdlib.h>
#include <stdio.h>

int main()
{
	int val;

	puts("***********************************");
	puts("* \t     -Level00 -\t\t  *");
	puts("***********************************");

	printf("Password:");

	val = scanf("%d");
	if (val == 5276){
		system("/bin/sh");
		puts("\nAuthentificated!");
		return 0;
	}
	puts("\nInvalid Password!");
	return 1:
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main()
{
	system("pwd");
	if (chdir("abc") == -1) {
    perror("chdir failed");
}
	system("pwd");
}

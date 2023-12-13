#include <stdio.h>
#include <stdlib.h>

int main()
{
	const char *c = "touch";
	printf("%s", getenv(c));
}
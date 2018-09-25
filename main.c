#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main (int argc, char** argv)
{
	if (argc > 2)
	{
		srand(time(NULL));
		printf("%s\n", argv[rand() % (argc-1) + 1]);
	}
	else
	{
		printf("Usage: rand <element 1> <element 2> ... <element n>\n");
	}
	return 0;
}

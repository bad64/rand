#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main (int argc, char** argv)
{
	srand(time(NULL));
	printf("%s", argv[rand() % (argc-1) + 1]);
	
	return 0;
}
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#if (defined (linux))
	#include <string.h>
	#include <regex.h>
#endif

void printHelp()
{
	printf("Usage: rand <element 1> <element 2> ... <element n>\n\n");
	
	#if (defined (linux))
		printf("Alternatively, you can pass an integer range thusly: rand <boundary 1>..<boundary 2>\n");
		printf("Boundary 1 does not need to be the lower boundary, neither does boundary 2 need to be the upper one, the program sorts them anyway.\n\n");
	#endif
}

int main (int argc, char** argv)
{
	//Is the user asking for help, or attempting to run the program normally ?
	if ((argc == 2) && ((strcmp(argv[1], "help") == 0) || (strcmp(argv[1], "?") == 0)))
	{
		printHelp();
	}
	else
	{	
		if (argc > 2)
		{
			srand(time(NULL));
			printf("%s\n", argv[rand() % (argc-1) + 1]);
		}
		else if (argc == 2)
		{
			#if (defined (linux))
				regex_t re;
				
				if (regcomp(&re, "[0-9]*..[0-9]*", REG_EXTENDED|REG_NOSUB) != 0)
				{
					printf("Error: regex failed to compile");
					exit(2);
				}
				else
				{
					if (regexec(&re, argv[1], 0, NULL, 0) == 0)
					{
						char *lstr, *rstr, *ptr;
						int lval, rval, index;	//rval will be max, lval will be min, index is the position of the first dot
						ptr = strchr(argv[1], '.');
						index = ptr - argv[1];
						
						//Sanity check
						if (!ptr)
						{
							printf("Argument error\n");
							exit(3);
						}
						else
						{						
							//Splitting input
							if (index == 0)
							{
								lstr = (char *)calloc(2, sizeof(char));
								lstr[0] = '0';
								lstr[1] = '\0';
							}
							else
							{
								lstr = (char *)calloc(index+1, sizeof(char));
								strncpy(lstr, argv[1], index);
								lstr[strlen(lstr)] = '\0';
							}
							
							if (strlen(argv[1]) - (index+1) == 0)
							{
								rstr = (char *)calloc(2 , sizeof(char));
								rstr[0] = '0';
								rstr[1] = '\0';
							}
							else
							{
								rstr = (char *)calloc(strlen(argv[1]) - (index+1) , sizeof(char));
								strncpy(rstr, argv[1] + (index+2), strlen(argv[1]) - (index+1));
								rstr[strlen(rstr)] = '\0';
							}
							
							//Assigning to rand boundaries
							if (strtol(lstr, NULL, 10) < strtol(rstr, NULL, 10))
							{
								lval = strtol(lstr, NULL, 10);
								rval = strtol(rstr, NULL, 10);
							}
							else if (strtol(lstr, NULL, 10) == strtol(rstr, NULL, 10))
							{
								printf("Range error\n");
								exit(1);
							}
							else
							{
								lval = strtol(rstr, NULL, 10);
								rval = strtol(lstr, NULL, 10);
							}
							
							srand(time(NULL));
							printf("%d\n", rand() % (rval - lval + 1) + lval);
							
							free(lstr);
							free(rstr);
						}
					}
					else if (regexec(&re, argv[1], 0, NULL, 0) == REG_NOMATCH)
					{
						printHelp();
						exit(1);
					}
					else
					{
						//Seriously, if the program gets there, I probably genuinely won't be able to tell what happened
						printf("An unknown error has happened\n");
						exit(4);
					}
				}
				
				regfree(&re);
			#else
				printf("Usage of integer ranges is not supported on Windows at the moment.\n"); //Mostly because I want to keep the program as a single file, and PCRE disagrees with that concept, sadly
				exit(1);
			#endif
		}
		else
		{
			printHelp();
			exit(1);
		}
	}
	return 0;
}

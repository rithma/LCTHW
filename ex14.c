#include <stdio.h>
#include <ctype.h>

//forward declarations
int can_print_it(char ch);
void print_letters(char arg[]);

void print_arguements(int argc, char *argv[])
{
	int i = 0;

	for (i = 0; i < argc; i++) {
		print_letters(argv[i]);
	}
}

//print_letters -
//for loop indexes through "non\0" characters, if can_print_it, prints char & ascii equiv 
//

void print_letters(char arg[])
{
	int i = 0;

	for (i = 0; arg[i] != '\0'; i++){
		char ch = arg[i];

		if (can_print_it(ch)) {
			printf("'%c' == %d == %X\n", ch, ch, ch);
		}
	}

	printf("\n");
}

//can_print_it
//passes in chars, returns 1 if char is alpha or blank.

int can_print_it(char ch)        
{
	return isalpha((int)ch) || isblank((int)ch);
}

int main(int argc, char *argv[])
{
	print_arguements(argc,argv);
	return 0;
}

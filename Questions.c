

/*EXCERCISE 10   
why is line 12 (the for loop-) a 2 dimensional array?   I dont understand why "argv[1][i]"  throughout the whole program
why not argv[i++]???

GOT IT!!!!     GOT IT!!!
the for loop is working with the 1st arguement on the command line(since the 0'th arguement is the program itself)
SO the arguement is an array of chars (string) and the 'i' is indexing into each char of the string. 



*/

int main(int argc, char*argv[])
{
	if (argc != 2) {
		printf("ERROR: you ned one arguement. \n");
		//this is how you abort a program
		return 1;
	}

	int i = 0;
	for (i = 0; argv[1][i] != '\0'; i++) {
		char letter = argv[1][i];

		switch (letter) {
			case 'a':
			case 'A':
			  printf("%d: 'A'\n", i);
			  break;

#  Starting to understand some more things

from Excercise 14 - 

The reason C needs forward declarations is b/c  c is from a tim before there was 
enough room or processor to store the whole program at once - 
so 
void print_letters(char arg[]);    //tells the computer what the function form is at the top of the file. 

can also be thought of as:
declaration   -  void print_letters(char arg[]);     //2 hamburgers today
definition    -  void print_letters(char arg[]);     //pay you on tuesday


a header file is just full of forward declarations

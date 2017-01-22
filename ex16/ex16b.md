its a dot when its not a pointer  
who.name = strdup(name);

its an arrow when it IS A POINTER
who->name = strdup(name);



```c


#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

//struct creates a new compound type that lets us reference these elements as one 
//or each by name.  
typedef struct {    //create a structure with 4 elements
	char *name;    //has to be a pointer b/c its a string? why?...
	int age;
	int height;
	int weight;
} Person;

//function with return type PersonPointer. 
Person * Person_create(char *name, int age, int height, int weight)
{
	Person *who;                    //working with pointers so we can use malloc
	who = malloc(sizeof(Person));   //malloc gives us a pointer to a piece of memory the size of Person.
    assert(who != NULL);                    //asserts who is a valid piece of memory

    who->name = strdup(name);
    who->age = age;
    who->height = height;
    who->weight = weight;

    return who;           
}

void Person_destroy(Person *who)		//a function to free the mem used by person
{
	assert(who != NULL);
	free(who->name);
	free(who);
}

void Person_print(Person *who)  //function
{
	printf("Name: %s\n",     who->name);
	printf("\tAge: %d\n",    who->age);
	printf("\tHeight: %d\n:",who->height);
	printf("\tWeight: %d\n", who->weight);
}

int main(int argc, char *argv[])
{
	//make 2 people structs
	Person *joe = Person_create("Joe Alex", 32,64, 140);

	Person *frank = Person_create("Frank Blank",20, 72, 180);

	//print them out and where they are in memory
	printf("Joe is at memory location %p:\n", joe);
	Person_print(joe);

	printf("Frank is at memory location %p: \n", frank);
	Person_print(frank);

	//make everyone age 20 years and print them again
	joe->age += 20;
	joe->height -= 2;
	joe->weight += 40;
	Person_print(joe);

	frank->age += 20;
	frank->weight += 20;
	Person_print(frank);

	//destroy them both so we clean up
	Person_destroy(joe);
	Person_destroy(frank);

	return 0;
}


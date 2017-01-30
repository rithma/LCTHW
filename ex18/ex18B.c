#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


void die(const char *message)
{
	if (errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}
	exit (1);
}

//  a typedef for a function pointer:
//int compare_cb(int a, int b);

/*
the function we are modelling the funcPtr after is:
int sorted_order(int a, int b)
{
    return (a > b) - (a < b);     //THIS IS THE FUNCTION "STYLE" OR "SIGNATURE" I WANT POINTERS TO...
}
*/
typedef int (*compare_cb) (int a, int b);   //see lines 50 - 


/**  a classic bubble sort, uses the compsre_cb to do the sorting
  *  memcpy()
  -  The C library function void *memcpy(void *str1, const void *str2, size_t n) 
  -  copies n characters from memory area str2 to memory area str1.
*/
int *bubble_sort(int *numbers, int count, compare_cb cmp)  //takes a pointer to numbers, a count, and a compare cb function ptr called CMP
{
    int temp = 0;		//the regular creation of variables on the stack
    int i = 0;
    int j = 0;
    int *target = malloc(count * sizeof(int));      //target points to a piece of mem the size of count times INT NUMBER OF BYTES OR WHATEVER

    if(!target)
    	die("memory error");

    memcpy(target, numbers, count * sizeof(int));   //copies "numbers" into "target"...

    for(i = 0; i < count; i++){ 					//the outer loop of the bubble sort
    	for(j = 0; j < count - 1; j++){				//the inner loop of the bubble sort
    		if (cmp(target[j], target[j + 1]) > 0) {   //here we call the CMP callback like its a normal function but instead of being the name of something we defined, its just a pointer to it. this lets the caller pass in anything it wants as long as it matches the signature of the compare_cb typedef 
    			temp = target [j + 1];				//41-43 the actual swapping operation where bubbl sort needs to do what it does
    			target[j + 1] = target[j];
    			target[j] = temp;
    		}
    	} 
    }
    return target;       //returns the newly created and sorted result array 'target'
}
           //here are three versions of the conpare_cb function type
int sorted_order(int a, int b)     //because these have the signature pointed to by compare_cb
{                                  //they can be used by another function like "dump"
	return (a > b) - (a < b);
}


int reverse_order(int a, int b)
{
	return (a < b) - (a > b);
}

int strange_order(int a, int b)
{
	if (a == 0 || b == 0) {
		return 0;
	} else {
		return a % b;
	}
}


int w_sheet(int a, int b)
{
     return (a * b);
}

    




void test_sorting(int *numbers, int count, compare_cb cmp)
{
    int i = 0;
    int *sorted = bubble_sort(numbers, count, cmp);

    if(!sorted){
    	die("failed to sort as requested.");
    }
    for(i = 0; i < count; i++){
    	printf(" %d ", sorted[i]);
    }
    printf("\n");

   

    free(sorted);
}



void dump(compare_cb cmp){
    int i = 0;
    unsigned char *data = (unsigned char *)cmp;
    for(i = 0; i < 25; i++) {
        printf("%x:", data [i]);
    }
    printf("\n");
}


void destroy(compare_cb cmp){
    int i = 80;
    unsigned char *data = (unsigned char *)cmp;
    for(i = 99; i < 100; i++) {
        data[i] = i;         //data pointer OVERWRITES DATA for compare function, replaces it with numbers
    }
    printf("\n");
}




int main(int argc, char *argv[])
{
	if (argc < 2) die("usage ex 18 2 9 43 28 8");

    int count = argc - 1;
    int i = 0;
    char **inputs = argv + 1;

    int *numbers = malloc(count * sizeof(int));
    if(!numbers) die("memory error");

    for (i = 0; i < count; i++){
    	numbers[i] = atoi(inputs[i]);
    }

test_sorting(numbers, count, sorted_order);    //test sorting passes in *numbers, count, and CMP functer from before
test_sorting(numbers, count, reverse_order);
test_sorting(numbers, count, strange_order);
test_sorting(numbers, count, w_sheet);

printf("SORTED:");
dump(sorted_order);

destroy(sorted_order);

printf("SORTED:");
dump(sorted_order);



free(numbers);

return (0);

}



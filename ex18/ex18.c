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

typedef int (*compare_cb) (int a, int b);

/**  a classic bubble sort, uses the compsre_cb to do the sorting
  *  memcpy()
  -  The C library function void *memcpy(void *str1, const void *str2, size_t n) 
  -  copies n characters from memory area str2 to memory area str1.
*/
int *bubble_sort(int *numbers, int count, compare_cb cmp)  //takes a pointer to numbers, a count, and a compare cb function ptr called CMP
{
    int temp = 0;
    int i = 0;
    int j = 0;
    int *target = malloc(count * sizeof(int));      //target points to a piece of mem the size of count times INT NUMBER OF BYTES OR WHATEVER

    if(!target)
    	die("memory error");

    memcpy(target, numbers, count * sizeof(int));   //copies "numbers" into "target"...

    for(i = 0; i < count; i++){
    	for(j = 0; j < count - 1; j++){
    		if (cmp(target[j], target[j + 1]) > 0) {
    			temp = target [j + 1];
    			target[j + 1] = target[j];
    			target[j] = temp;
    		}
    	} 
    }
    return target;
}
    
int sorted_order(int a, int b)
{
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

test_sorting(numbers, count, sorted_order);
test_sorting(numbers, count, reverse_order);
test_sorting(numbers, count, strange_order);

free(numbers);

return (0);

}




















































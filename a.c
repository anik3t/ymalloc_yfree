#include <stdio.h>
#include <string.h>
#include "ymalloc.h"

int main(void) 
{
	int i,sum=0;
	int* x= (int*) ymalloc(10*sizeof(int));

	printf("Enter elements: ");
   	for(i = 0; i < 10; ++i)
    	{
        scanf("%d", x + i);
        sum += *(x + i);
    	}

	printf("Sum = %d", sum);
	yfree(x);


	return 0;
}

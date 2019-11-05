#include <stdio.h>
#include <stdlib.h>
#include "ymalloc.h"

int main(void) 
{
	int i,sum=0;
	
	int* x= (int*) ymalloc(10*sizeof(int));

	printf("Enter elements: ");
   	for(i = 0; i < 3; ++i)
    	{
	printf("Address : %p\n",x+i);
        scanf("%d", x + i);
        sum += *(x + i);
    	}

	printf("Sum = %d\n", sum);
	
	yfree(x);
	
	

	return 0;
}

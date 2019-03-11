#include<stdio.h>
#include<stdlib.h>
#define SIZE 1000
void *start_add,*end_add;
typedef struct unallocated{
	void *s_add;
	int size;
	struct unallocated *next;
}unalloc;
unalloc *ublock;

typedef struct allocated{
	void *st_add;
	int size;
	struct allocated *next;
}alloc;
alloc *ablock;


void yalloc(){
	start_add=(void*)malloc(sizeof(SIZE));
	end_add=start_add+SIZE;
	printf("%p\n",start_add);
	printf("%p\n",end_add);
}
void* ymalloc(int x){
	alloc* head, *temp;
	temp=NULL;
	if(x<=ublock->size){
		temp->st_add=ublock->s_add;
		temp->size=x;
		ublock->s_add=ublock->s_add+x+1;
		temp->next=NULL;
		return ablock->st_add;
	}
	else if(head=NULL)
		head=temp;
	else
		printf("Requested memory not available");
	
}
void main(){

	
	unalloc ublock;    
	alloc* ablock=NULL;
	yalloc();
	printf("start add in main %p\n",start_add);
//	ublock->s_add=0;
	ublock.s_add=start_add;
	ublock.size=SIZE;
	ublock.next=NULL;

	//ablock->next=NULL;
	int *temp;
	temp=ymalloc(100);
}

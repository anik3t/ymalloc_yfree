/*ymalloc_yfree
 *
 *Allocating big chunck of memory with yalloc once using malloc
 *
 *Maintaining separate lists of unallocated and allocated blocks, where unallocated list keeps the output of yalloc

 *ymalloc requesting for memory block from unallocated list
 *
 * yfree freeing out the allocated memory block, ordering the unallocated list according to addresses 
 * and then merging the blocks with contiguous addresses
 */

#include<stdio.h>
#include<stdlib.h>
#define SIZE 1024*1024*8
#include<stdbool.h>

typedef struct memory{
	long int size;		//keeping the block size required by the user, irrespective of meta data
	struct memory *next;	//  pointing the next memory block in allocated/unallocated list
}node;	

node *ublock=NULL,*ablock=NULL;
//merge sort for ordering the random unallocated block for merging them into continuous block 
node *umergesort(node *head);
node *merge(node *head1,node *head2);

node* joinublock(node* ublock);
//merging the block into a continous memory according to there addresses
bool init=false;
//initializing yalloc once in a program

void* yalloc(){
	//node *ublock;
	//start_add=(void*)malloc(SIZE+sizeof(node));
	ublock=(void*)malloc(SIZE+sizeof(node)); 	//ublock 
	ublock->size=SIZE;
	ublock->next=NULL;
	//ublock->self=start_add;
	//ablock=NULL;
	//ablock->size=0;
	return ublock;
}

void* ymalloc(long int x){
	//node *ublock,*ablock,
	node   *temp,*buff;
	if(!init){
	ublock=yalloc();
	init=true;
	}
	temp=ublock;
	//printf("%ld",temp->size);
	do{
		if((temp->size)==x){
			ablock = temp;
			ablock->next = NULL;
			buff->next = temp->next;
			temp = buff;

			return ablock+sizeof(node);
		}
		else if((temp->size)>x){
			if( ( (sizeof(node)+temp->size)-(x+sizeof(node)) ) > sizeof(node) ){
			//worst case checking to keep atleast one block of 1 byte + sizeof(node)
				if(ablock==NULL){
					ablock = temp;
					//printf("%d",ablock->size);		
					ablock->size = x;
				}	
				else{
					ablock->next = temp;
					ablock = ablock->next;
				}
				ablock->next=NULL;
				temp = temp+sizeof(node)+x;
				temp->size = (temp->size) - x - sizeof(node);
				// meta block of current ublock(temp) is ignored as it is not considered in size and directly allocated to ablock
				buff->next = temp;
				temp = buff;
				ablock->next = NULL;
				return ablock+sizeof(node);			
			}
		}


		buff=temp;                      //storing current node in buffer
	}while(temp=temp->next);
	return NULL; //if x is greater than unallocated block size
}

void yfree(void* t){
	node* atemp,*buff,*utmp;
	atemp = ablock;
	utmp = ublock;
	t = t-sizeof(node);
	do{
		if(t==atemp){
			buff->next = atemp->next;
			while((utmp = utmp->next)!= NULL);
			//freeing allocated block and adding it to unallocated list
			utmp->next=atemp;
			utmp=utmp->next;
			utmp->next=NULL;
		}	
		buff=atemp;
	}while(atemp=atemp->next);
	ublock = umergesort(ublock);
	ublock = joinublock(ublock);
}

node* umergesort(node* head) {
	node* head1;
	node* head2;
	if((head == NULL) || (head->next == NULL))
		return head;
	head1 = head;
	head2 = head->next;
	while((head2 != NULL) && (head2->next != NULL)) {
		head = head->next;
		head2 = head->next->next;
	}
	head2 = head->next;
	head->next = NULL;

	return merge(umergesort(head1), umergesort(head2));
}

node* merge(node* head1, node* head2) {
	node* head3;

	if(head1 == NULL) 
		return head2;

	if(head2 == NULL) 
		return head1;

	if(head1 < head2) {
		head3 = head1;
		head3->next = merge(head1->next, head2);
	} else {
		head3 = head2;
		head3->next = merge(head1, head2->next);
	}

	return head3;
}

node* joinublock(node* ublock){
	node* temp;
	temp=ublock;
	do{
		if((temp + sizeof(node) + temp->size)==temp->next){	//checking the presence of successive address block
		temp->size = temp->size + ((temp->next)->size) + sizeof(node);
		temp->next = (temp->next)->next;
		}
	}
	while(temp=temp->next);
	return ublock;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

/*Struct Area !!! */
///////////////////////////////////////////////////////////

typedef struct Node {
    int data;
    struct Node * next;
} node;

///////////////////////////////////////////////////////////

node * head;
node * head2;

void print_data(void * a){
    node * tmp;
    tmp = (node *)a;
    printf("printing data\n\n data: %d, ptr: %p\n\n",tmp -> data,tmp -> next);
}

int main(int argc, char * argv[], char * envp[] ){
    
    void * curr_pb;
    void * a;
    void * a1;
    void * a2;


    printf("Size of node: *head %ld, head: %ld\n", sizeof(* head), sizeof(head));
    printf("curr_pb: %p, a: %p, a1: %p \n\n",curr_pb, a,a1);
    
    a = sbrk(0);
    printf("location of prog break: %p , 0x%x \n", a,a);
    
    head = (node *) malloc(sizeof(head));
    //head2 = (node *) malloc(sizeof(head));
    
    a = sbrk(0);
    printf("> location of prog break after malloc: %p , 0x%x \n", a,a);

    a1 = sbrk(sizeof(*head)); 
    head = a1;
    printf("> next location of prog break: %p , %ld \n", a1, a1-a);
    head -> data = 999;

    
    a2 = sbrk(sizeof(*head)); 
    printf("> next 2 location of prog break: %p , %ld \n", a2, a2-a);
    head -> next = a2;
    print_data(head);

   // printf("Printing data \n data = %d\n\n", a1 -> data);



    curr_pb = sbrk(0);
    printf("> current prg_brk %p, %ld\n",curr_pb, curr_pb - a1);

    printf("ENND !!!\n");

    return 0;
}

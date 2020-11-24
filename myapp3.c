#include <stdio.h>
#include <stdlib.h>

#include "mull.h"


typedef struct AppNode{
    int data1;
    char word[10];
    
    struct AppNode * next;
} appNode;



int main(){
    int x, id = 9;
    void * q;
    void * a;
    void * b;

    appNode * curr_app;
    appNode * curr1;
    appNode * curr2;
    appNode * curr3;
    ctest1(&x);
    printf("Valx=%d\n",x);
    printf("Size cur_app %ld BEGIN ! \n,", sizeof(*curr_app));
    
    //q = sbrk(0);

    id = mullinit(sizeof(*curr_app )) ; //change 2nd arg to 32 
    printf("Returned Id: %d\n",id); 
     

    
    curr_app = mulloc(id);
    curr_app -> data1 = 11;
    printf("  %p Value curr_app : %d\n", curr_app, curr_app -> data1);
    q = (void *)curr_app;

    curr1 = mulloc(id);
    curr1 -> data1 = 22;
    printf("  %p Value curr1 : %d\n",curr1, curr1 -> data1);
    printf("p2: %p, p1: %p, Diff ptr 2-1: %ld, \n ", curr1, curr_app,
            ((void *)curr1 - (void *)curr_app));

    curr2 = mulloc(id);
    curr2 -> data1 = 33;
    printf("Value curr2 : %d\n", curr2 -> data1);
    printf("p2: %p, p1: %p, Diff ptr 2-1: %ld, \n ", curr2, curr1,
            ((void *)curr2 - (void *)curr1));
    
    curr3 = mulloc(id);
    curr3 -> data1 = 44;
    printf("Value curr3 : %d\n", curr3 -> data1);

    printf("Value curr_app : %d\n", curr_app -> data1);
    for (int i = 0; i < 130; i++){
        curr3 = mulloc(id);
        curr3 -> data1 = 7;
        printf("i: %d, Value curr : %d\n",i,  curr3 -> data1);
    }

    printf("FOR \n");
    for (int i = 0; i < 130; i++ )
    printf("i = %d, Value curr_app2 : %d \n", i,(curr_app +i) -> data1);
    
    (curr_app + sizeof(*curr_app)) -> data1 = 777;
    printf("Value curr_app2 : %d\n", (curr_app+sizeof(*curr_app)) -> data1);

    mullfree();

    /*for (int i= 0; i < 10; i++){
        curr_app[i] -> data1 = i+1;
    }
    */


    /*
    node * head = NULL;
    node * tmp = NULL;

    head = create(10 , head);

    for(int i = 1; i < 10; i++){
         head = append(i, head);
         printf("%d\n", i);
     }
    printf("Append Done !\n");

    tmp = head;

    for (tmp = head; tmp != NULL; tmp = tmp -> next  ){
         printf("%d,%p \n",tmp -> data, tmp -> next);
    }

    freeList(head);
    printf("%d", head -> data);
    */
    

   return 0;
}

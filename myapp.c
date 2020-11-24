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
    

    appNode * curr_app;
    appNode * curr1;
    appNode * curr2;
    appNode * curr3;
    ctest1(&x);
    printf("Valx=%d\n",x);
    printf("Size cur_app %ld\n,", sizeof(*curr_app));
    


    id = mullinit(sizeof(*curr_app ), 8) ; //change 2nd arg to 32 
    printf("Returned Id: %d\n",id); 
  

    id = mullinit(sizeof(*curr_app ), 8) ; //change 2nd arg to 32 
    printf("Returned Id: %d\n",id); 
   
    id = mullinit(sizeof(*curr_app ), 10) ; //change 2nd arg to 32 
    printf("Returned Id: %d\n",id); 
    
    curr_app = mulloc(id);
    curr_app -> data1 = 11;
    printf("Value curr_app : %d\n", curr_app -> data1);
    
    curr1 = mulloc(id);
    curr1 -> data1 = 22;
    printf("Value curr1 : %d\n", curr1 -> data1);

    curr2 = mulloc(id);
    curr2 -> data1 = 33;
    printf("Value curr2 : %d\n", curr2 -> data1);
    
    curr3 = mulloc(id);
    curr3 -> data1 = 44;
    printf("Value curr3 : %d\n", curr3 -> data1);

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

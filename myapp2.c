#include <stdio.h>
#include <stdlib.h>

#include "mull.h"
#define MAXNODES 10

typedef struct AppNode{
    long data1;
    //char word[10];
    
    struct AppNode * next;
} appNode;

int id;

appNode * createL(int data, appNode * head){
    appNode * curr;
    appNode * tmp;

    if (head == NULL){
        head = mulloc(id);
        printf("> ptr: %p, ",head);
        head -> data1 = data;
        head -> next = NULL;
    }
    else{
        curr = head;
        while(curr -> next ){
            curr = curr -> next;
        }
        tmp = mulloc(id);
        if (tmp == NULL)
            printf("NULL ptr\n");
        printf("> ptr: %p, ",tmp);
        tmp -> data1 = data;
        tmp -> next = NULL;
        curr -> next = tmp;
    }
    return head;

}

void printAppList(appNode * head){
    int i = 0;
    printf("AT PRINT \n");
    while(head -> next){
        printf("i = %d, Val :  %ld\n",i, head -> data1);
        i++;
        head = head -> next;
    }   
    printf("END OF LIST \n");
}

int main(){
    int x;
    void * q;
    void * a;
    void * b;

    appNode * head;
    appNode * curr_app;
    appNode * curr1;
    appNode * curr2;
    appNode * curr3;
    FILE * fd  = fopen("write", "a+");
    
    ctest1(&x);
    printf("Valx=%d\n",x);
    printf("Size cur_app %ld BEGIN ! \n,", sizeof(*curr_app));
    
    //q = sbrk(0);

    id = mullinit(sizeof(*curr_app )) ; //change 2nd arg to 32 
    printf("Returned Id: %d\n",id); 
    
    
          //
    for(int i = 0; i < MAXNODES; i++){
        head = createL(i,head);
        printf("> Added: %d", i );
    }
    
    printAppList(head);

    while (head){
        curr_app = head;
        mullfree(curr_app);
        head = head -> next;

    }
    
    /*
    
    curr_app = mulloc(id);
    curr_app -> data1 = 11111;
    
    //
    printf("  %p Value curr_app : %ld\n", curr_app, curr_app -> data1);
    q = (void *)curr_app;

    curr1 = mulloc(id);
    curr1 -> data1 = 22;
    printf("  %p Value curr1 : %ld\n",curr1, curr1 -> data1);
    printf("p2: %p, p1: %p, Diff ptr 2-1: %ld, \n ", curr1, curr_app,
            ((void *)curr1 - (void *)curr_app));

    curr2 = mulloc(id);
    curr2 -> data1 = 33;
    printf("Value curr2 : %ld\n", curr2 -> data1);
    printf("p2: %p, p1: %p, Diff ptr 2-1: %ld, \n ", curr2, curr1,
            ((void *)curr2 - (void *)curr1));
    
    curr3 = mulloc(id);
    curr3 -> data1 = 44;
    printf("Value curr3 : %ld\n", curr3 -> data1);
    //
    printf("Value curr_app : %ld\n", curr_app -> data1);
    for (int i = 0; i < 34; i++){
        curr3 = mulloc(id);
        curr3 -> data1 = i;
        printf("i: %d, ptr: %p, Value curr : %ld\n",i,curr3 , curr3 -> data1);
        fprintf(fd, "i = %d, Val curr : %p, data: %ld \n",i,curr3,curr3 -> data1 );
    }

    printf("FOR \n");
    for (int i = 0; i < 34; i++ )
    //printf("i = %d, Value curr : %ld   \n", i,(curr_app +i) -> data1);
        printf("i = %d, Value curr : %ld  %p \n", i,(curr_app +i) -> data1, curr_app+i);
    
    (curr_app + sizeof(*curr_app)) -> data1 = 777;
    printf("Value curr_app2 : %ld\n", (curr_app+sizeof(*curr_app)) -> data1);
    
    

    fclose(fd);
    */

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

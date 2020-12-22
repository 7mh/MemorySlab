#include <stdio.h>
#include <stdlib.h>

#include "mull.h"
#define MAXNODES 100

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

   return 0;
}

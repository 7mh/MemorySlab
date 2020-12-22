//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
#include "mull.h"

long countl = 0;
long countf = 0;
int tally_created = 0;
int remaining_cell = 0;
int id_count = 0;

void ctest1(int *i)
{
   *i=5;
}


//void create_tally( int id, int n_cells, int cell_size, int used_c,
//        unsigned int used_bit){

void print_tally(){
    tally * curr;
    curr = head;
    if (curr == NULL){
        return;
    }
    while (curr){
        printf("Id: %d, tot_cell: %d, cell_size:%d, used_c: %d, used_bit: %lu, start_ptr: %p, next: %p\n", curr -> id,
                curr->tot_cell, curr->cell_size, curr-> used_c, curr-> used_bit, curr-> start_ptr, curr-> next);
        curr = curr -> next;
    }
}

tally * create_tally(int id, size_t cell_size, int n_cells){
    tally* curr;
    //tally * new_node = (* tally) malloc(sizeof(tally));
    tally * new_node;
    int t = 1;          // to fill head->used_bit
    int * tmp;
    // check if Llist header is already malloced
    //if (tally_created == 0){    
    if (head == NULL){ 
        //tally_created = 1;
        printf("building LinkList \n");
        
        head = sbrk(sizeof(* head));
        if (head == (void *)-1){
            printf("Error creating head tally block\n");exit(0);}
        head -> id = id;
        
        //if (n_cells > 0){       //MAXCELLS = 32
            
        head -> tot_cell = MAXCELLS;   // starts with 1
        head -> used_c = 0L;
        head -> cell_size = cell_size;
        head -> used_bit = 0L;
        //}

        // malloc the cells for this block    
        //head -> start_ptr = sbrk(sizeof(cell_size)* MAXCELLS*3);
        head -> start_ptr = sbrk((cell_size)* MAXCELLS);
    
        head -> next = NULL;

        printf("Printing PTR \n");
        
        for (int i = 0; i < 5; i++){
            tmp = (head -> start_ptr)+i;
            printf("ptr : %p, val: %x\n", (head -> start_ptr)+i,~*tmp);
        }
    
        //print_tally();  // prints entire linked list

    }
    else{
        printf("Appending LinkList   pgrmBrk: %p\n", sbrk(0));
        tally * new_node;
        tally * cur ;
        cur = head;

        new_node = sbrk(sizeof(* new_node));
        if (new_node == (void *)-1){
            printf("Error creating new_node tally block\n");exit(0);}
        new_node -> id = id;
        
        if (n_cells > 0){       //MAXCELLS = 32
            
            new_node -> tot_cell = n_cells;   // starts with 1
            new_node -> used_c = 0;
            new_node -> cell_size = cell_size;
            new_node -> used_bit = 0;
        }

        //new_node -> start_ptr = sbrk(sizeof(cell_size)* MAXCELLS*3);
        new_node -> start_ptr = sbrk((cell_size)* MAXCELLS);
        
        new_node -> next = NULL;
        
        while(cur -> next != NULL){
            cur = cur -> next;
        }
        cur -> next = new_node;

        printf("\nPRINTING entire list \n");
        //print_tally();                    //EXTRA
        
    }
    return head;
}


int mullinit(size_t cell_size ){
    
    int id_out = -1;
    int id_hit = -1;    // in mem_cell_size array
    startPrgBrk = sbrk(0);
    printf("STart Program break: %p\n", startPrgBrk);
    // fill mem_cell_size array
    if (head == NULL){
    
        create_tally(id_count,cell_size, MAXCELLS);
        id_out = id_count;    
        mem_cell_size[id_count] = cell_size; 
        id_count++;                 // dont check entire array
    }
    else{
        //create_tally(id_count, cell_size, MAXCELLS);
        id_out = id_count;
        mem_cell_size[id_count] = cell_size; 
        id_count++;                 // dont check entire array
    }

    return id_out;
}

//void * mulloc(int id, size_t cell_size, int n_cells){
void * mulloc(int id ){
    int id_hit = -1;
    int t;
    void * ret_ptr;

    tally * cur;

    cur = head;

    while(cur){
        if ((cur -> id == id) && (cur -> used_c < (MAXCELLS))){
            break;
        }
        cur = cur -> next;
    }
    printf("\n\nAt MULLOC CALL !!! \t\t\t%ld\nMAtch from linked list\n",countl);
    countl ++;
    printf("Id: %d, tot_cell: %d, cell_size:%d, used_c: %d, used_bit: %lu, start_ptr: %p, countl: %ld, next: %p \n", cur -> id,
                cur->tot_cell, cur->cell_size, cur-> used_c, cur-> used_bit, cur-> start_ptr,countl, cur-> next);
    
    //filling
    ret_ptr = cur -> start_ptr + (cur->used_c * cur->cell_size);
    //ret_ptr = (cur -> start_ptr) + (cur->used_c +2);
    cur -> used_c += 1;
    if (cur -> used_c  == MAXCELLS){
        printf("\t\t CREATING NEW BLOCK !!! \n");
        create_tally(cur-> id, cur-> cell_size, MAXCELLS);
    }

    // marking bits for used cells    
    for (int i = 0; i < 32 ; i++ ){
        
        t = ((1) << i);
        if ((cur -> used_bit & t) == 0){
            cur -> used_bit |= t;
            break;
        }
    }
    printf("after changing bit    prgBrk: %p\n", sbrk(0));
    print_tally();                    //Extra

    


    /*for (int i =0; i < SIZELIST; i++){
        if (cur -> cell_size == mem_cell_size[i]){
                id_hit = i;
        }
    }
    printf("id_arg: %d, id_hit: %d\n", id, id_hit);
    */
    return ret_ptr;
}

void mullfree(void * tcur){
    //int t;
    int found = 0;
    static int freed = 0;
    int missed = 0;
    
    static tally * cur = {0};     //last block
    if (cur == NULL){
        //printf("> Init Tally head : %p \n", head);
        cur = head;
    }

    for (int i = 0; i < 2; i++){
        if (cur == NULL){
            //printf(" \t\tGoing over Tally again from start\t");
            cur = head;
        }
        if (found == 1)
            break;
        while((cur) ){
        if ((tcur >= cur->start_ptr) && 
                (tcur <= (cur->start_ptr+((cur->tot_cell-1 )*cur->cell_size) ) ) ){
                cur ->used_c--;
                cur -> used_bit =  cur -> used_bit >> 1;
                printf("BLOCK freed: !!! ptr:%p  start:%p  end:%p\n",tcur,
                        cur->start_ptr, 
                          cur->start_ptr+((cur->tot_cell-1)*cur->cell_size ));
                freed++;
                found = 1;
                break;
                }
        printf("NOT found! go next block\n");
        cur = cur -> next;
        missed++;
    }
    }
    printf("\n\nFree STATUS !!!! alreadyfreed_count: %d, Null: %d cur: %p\n", freed,missed, cur);

    //printf("Blocks Freed: %ld, ptr: %p \t end:%p \n", countf, tcur, tcur+(3*16));

}








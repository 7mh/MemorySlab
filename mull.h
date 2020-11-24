#ifndef MULL_H_
#define MULL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//#ifndef MAXCELLS
//#define MAXCELLS 10576    
#define MAXCELLS 4    
#define SIZELIST 512
//#endif

typedef struct Node{
        int data;
        struct Node * next;
   }node;

 

////////////////////////////////
//for Tally linked list

typedef struct Tally{
     int id;
     int tot_cell;          // starts with 1, Can change Longint
     int cell_size;
     int used_c;            // starts with 1
     unsigned long used_bit;
     void * start_ptr;

     struct Tally * next;

 } tally;

void * startPrgBrk;
int mullinit(size_t cell_size);
//void * mulloc(int id, size_t cell_size, int n_cells);
void * mulloc(int id );
tally * create_tally(int id, size_t cell_size, int n_cells);
void print_tally();
void mullfree();


tally * head;
size_t mem_cell_size [SIZELIST];

////////////////////////////////



////////////////////////////////
// for .so file testing
void ctest1(int *);
void ctest2(int *);
////////////////////////////////

////////////////////////////////
// for genaric Link list
node * create(int data, node * next);
node * append (int data, node * head);
node * insert_before(int data, node * head, node * next);
void freeList (node * head);
////////////////////////////////


#endif

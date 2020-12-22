
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mull.h"

#define N   100L
/*
#ifdef DEBUG
#define N   1048576L
#else
#define N  33554432L
#endif
*/
/*
 * malloc data for mini test on CS with gcc -O3:
 *
 * 662938 nodes
 * 0.609u 0.008s 0:00.61 98.3%	0+0k 0+0io 0pf+0w
*/

/*
 * malloc data for big test on CS with gcc -O3:
 *
 * 21210653 nodes
 * 48.298u 0.261s 0:48.60 99.8%	0+0k 0+0io 0pf+0w
*/

// redefine these in library

#define ALLOCATIONMACRO(X)  mulloc(X)
#define INITMACRO(X)        mullinit(X)
#define FREEMACRO(X)        mullfree(X)

typedef struct node {
    long x;
    struct node *left, *right;
} TREENODE;

TREENODE *makeleaf(int x);
long countnodes(TREENODE *t);
void hang(TREENODE *parent, long x);
void freetree(TREENODE *t);

int id;
int count = 0;

int main(int argc, char *argv[])
{
    TREENODE *root;
    long i;
    long x;

    srandom(2);

    id = INITMACRO(sizeof(TREENODE));

    root = 0;
    for(i=0L;i<N;i++){
        x = random() % N;
        if(!root)
            root = makeleaf(x);
        else
            hang(root, x);
    }

    printf("%ld nodes made, count: %d\n", countnodes(root), count);

    freetree(root);
}
TREENODE *makeleaf(int x)
{
    TREENODE *t;

    t = (TREENODE *) ALLOCATIONMACRO(id);
    count ++;
    t->x = x;
    t->left = t->right = 0;
    return t;
}
void hang(TREENODE *parent, long x)
{
    for(;;){
        if(x == parent->x)
            return;
        if(x < parent->x){
            if(parent->left){
                parent = parent->left;
            } else {
                parent->left = makeleaf(x);
                return;
            }
        } else {
            if(parent->right){
                parent = parent->right;
            } else {
                parent->right = makeleaf(x);
                return;
            }
        }
    }
}
long countnodes(TREENODE *t)
{
    if(t == 0)
        return 0L;
    return 1L + countnodes(t->left) + countnodes(t->right);
}

void freetree(TREENODE *t)
{
    if(t == 0)
        return;
    freetree(t->left);
    freetree(t->right);
    FREEMACRO(t);
}



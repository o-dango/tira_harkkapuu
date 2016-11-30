
#ifndef BINTREE
#define BINTREE

struct tree {

    int node;
    int status;
    struct tree *pLeft;
    struct tree *pRight;

}; typedef struct tree *pTree;

void rotate_left(pTree *, int *);
void rotate_right(pTree *, int *);
int addNode(pTree *, int, int *);
void emptyTree(pTree);
int getHeight(pTree, int);
int searchKey(pTree, int);
#endif

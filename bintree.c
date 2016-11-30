#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "bintree.h"
#include "misc.h"
#include <wchar.h>
#include <locale.h>


void rotate_left(pTree *pNode, int *status) {

    pTree child, grandchild;
    child = (*pNode)->pLeft;
    FILE* pFile;

    if((pFile = fopen("binääripuu.txt", "a")) == NULL) {

        perror("Tiedoston avaus epäonnistui\n");
        exit(1);

    }

    if(child->status == 1) {  //LL-kierto

        fprintf(pFile, "Tehdään LL-kierto\n\n\n");
        (*pNode)->pLeft = child->pRight;
        child->pRight = *pNode;
        (*pNode)->status = 0;
        (*pNode) = child;

    }

    else { //LR-kierto

        fprintf(pFile, "Tehdään LR-kierto\n\n\n");
        grandchild = child->pRight;
        child->pRight = grandchild->pLeft;
        grandchild->pLeft = child;
        (*pNode)->pLeft = grandchild->pRight;
        grandchild->pRight = *pNode;

        switch(grandchild->status) {

            case 1:
            (*pNode)->status = -1;
            child->status = 0;
            break;

            case 0:
            (*pNode)->status = child->status = 0;
            break;

            case -1:
            (*pNode)->status = 0;
            child->status = 1;
        }

        *pNode = grandchild;

    }

    (*pNode)->status = 0;
    *status = 0;
    fclose(pFile);

}


void rotate_right(pTree *pNode, int *status) {

    pTree child, grandchild;
    child = (*pNode)->pRight;
    FILE* pFile;

    if((pFile = fopen("binääripuu.txt", "a")) == NULL) {

        perror("Tiedoston avaus epäonnistui\n");
        exit(1);

    }

    if(child->status == -1) {  //RR-kierto

        fprintf(pFile, "Tehdään RR-kierto\n\n\n");
        (*pNode)->pRight = child->pLeft;
        child->pLeft = *pNode;
        (*pNode)->status = 0;
        (*pNode) = child;

    }

    else { //RL-kierto

        fprintf(pFile, "Tehdään RL-kierto\n\n\n");
        grandchild = child->pLeft;
        child->pLeft = grandchild->pRight;
        grandchild->pRight = child;
        (*pNode)->pRight = grandchild->pLeft;
        grandchild->pLeft = *pNode;

        switch(grandchild->status) {

            case 1:
            (*pNode)->status = 1;
            child->status = 0;
            break;

            case 0:
            (*pNode)->status = child->status = 0;
            break;

            case -1:
            (*pNode)->status = 0;
            child->status = -1;
        }

        *pNode = grandchild;

    }

    (*pNode)->status = 0;
    *status = 0;
    fclose(pFile);

}


int addNode(pTree *pNode, int number, int *stable) {

    int temp = 0;

    if(!(*pNode)) {

        *stable = 1;
        if(!(*pNode = (pTree)malloc(sizeof(pTree)))) {
            perror("Muistinvaraus epäonnistui!");
            exit(1);
        }

        (*pNode)->pLeft = (*pNode)->pRight = NULL;
        (*pNode)->status = 0;
        (*pNode)->node = number;

    }

    else if(number < (*pNode)->node) {

        temp = addNode(&(*pNode)->pLeft, number, stable);

        if(*stable) {

            switch((*pNode)->status) {

                case -1:
                (*pNode)->status = 0;
                *stable = 0;
                break;

                case 0:
                (*pNode)->status = 1;
                break;

                case 1:
                rotate_left(pNode, stable);
                break;

            }

        }

    }

    else if(number > (*pNode)->node) {

        temp = addNode(&(*pNode)->pRight, number, stable);

        if(*stable) {

            switch((*pNode)->status) {

                case 1:
                (*pNode)->status = 0;
                *stable = 0;
                break;

                case 0:
                (*pNode)->status = -1;
                break;

                case -1:
                rotate_right(pNode, stable);
                break;

            }

        }

    }

    else {

        *stable = 0;
        //printf("Luku %d on jo puussa\n", number);
        temp = 1;

    }

    return temp;

}


void emptyTree(pTree pNode) {

    if(pNode) {

        emptyTree(pNode->pRight);
        emptyTree(pNode->pLeft);
        free(pNode);

    }

}


int getHeight(pTree pNode, int current) {

    int h = 0;
    int temp;

    if(pNode) {

        h = current;
        temp = getHeight(pNode->pLeft, current+1);
        h = (h >= temp) ? h : temp;
        temp = getHeight(pNode->pRight, current+1);
        h = (h >= temp) ? h : temp;

    }

    return h;

}


int searchKey(pTree pNode, int key) {

	if(pNode == NULL) {

		return 0;

	}

	else if(pNode->node == key) {

		return pNode->node;

	}

	else if(pNode->node > key) {

		return searchKey(pNode->pLeft, key);

	}

	else {

		return searchKey(pNode->pRight, key);

	}

}

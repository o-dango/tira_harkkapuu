#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "bintree.h"
#include "misc.h"
#include <wchar.h>
#include <locale.h>


void rotate_left(pTree *pNode, int check, int *status) {

    pTree child, grandchild;
    child = (*pNode)->pLeft;
    FILE* pFile;

    if(check == 0) {

        if((pFile = fopen("binääripuu.txt", "a")) == NULL) {                    /*avataan tiedosto kirjoittamista varten*/

            perror("Tiedoston avaus epäonnistui\n");
            exit(1);

        }

    }

    if(child->status == 1) {  //LL-kierto

        if(check == 0)
            fprintf(pFile, "Tehdään LL-kierto\n\n\n");

        (*pNode)->pLeft = child->pRight;
        child->pRight = *pNode;
        (*pNode)->status = 0;
        (*pNode) = child;

    }

    else { //LR-kierto

        if(check == 0)
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

    if(check == 0)
        fclose(pFile);

}


void rotate_right(pTree *pNode, int check, int *status) {

    pTree child, grandchild;
    child = (*pNode)->pRight;
    FILE* pFile;

    if(check == 0) {

        if((pFile = fopen("binääripuu.txt", "a")) == NULL) {                        /*avataan tiedosto kirjoittamista varten*/

            perror("Tiedoston avaus epäonnistui\n");
            exit(1);

        }

    }

    if(child->status == -1) {  //RR-kierto

        if(check == 0)
            fprintf(pFile, "Tehdään RR-kierto\n\n\n");

        (*pNode)->pRight = child->pLeft;
        child->pLeft = *pNode;
        (*pNode)->status = 0;
        (*pNode) = child;

    }

    else { //RL-kierto

        if(check == 0)
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

    if(check == 0)
        fclose(pFile);

}


int addNode(pTree *pNode, int number, int check, int *stable) {                 /*lisätään luku puuhun*/

    int temp = 0;

    if(!(*pNode)) {

        *stable = 1;
        if(!(*pNode = malloc(sizeof(pTree)))) {                                 /*muistinvaraus*/
            perror("Muistinvaraus epäonnistui!");
            exit(1);
        }

        (*pNode)->pLeft = (*pNode)->pRight = NULL;
        (*pNode)->status = 0;
        (*pNode)->node = number;

    }

    else if(number < (*pNode)->node) {                                          /*jos lisättävä luku on pienempi kuin nykyinen solmu*/

        temp = addNode(&(*pNode)->pLeft, number, check, stable);

        if(*stable) {

            switch((*pNode)->status) {                                          /*tarkastetaan onko puu tasapainossa*/

                case -1:
                (*pNode)->status = 0;
                *stable = 0;
                break;

                case 0:
                (*pNode)->status = 1;
                break;

                case 1:
                rotate_left(pNode, check, stable);                                     /*jos puu ei ole tasapainossa*/
                break;

            }

        }

    }

    else if(number > (*pNode)->node) {                                          /*jos lisättävä luku on suurempi kuin nykyinen solmu*/

        temp = addNode(&(*pNode)->pRight, number, check, stable);

        if(*stable) {

            switch((*pNode)->status) {                                          /*tarkastetaan onko puu tasapainossa*/

                case 1:
                (*pNode)->status = 0;
                *stable = 0;
                break;

                case 0:
                (*pNode)->status = -1;
                break;

                case -1:
                rotate_right(pNode, check, stable);                                    /*jos puu ei ole tasapainossa*/
                break;

            }

        }

    }

    else {                                                                      /*jos luku löytyy jo puusta*/

        *stable = 0;
        //printf("Luku %d on jo puussa\n", number);
        temp = 1;

    }

    return temp;

}


void emptyTree(pTree pNode) {                                                   /*muistin vapautus*/

    if(pNode) {

        emptyTree(pNode->pRight);
        emptyTree(pNode->pLeft);
        free(pNode);

    }

}


int getHeight(pTree pNode, int current) {                                       /*haetaan puun syvyys*/

    int h = 0;
    int temp;

    if(pNode) {

        h = current;
        temp = getHeight(pNode->pLeft, current+1);
        h = (h >= temp) ? h : temp;                                             /*jos nykyinen taso on pienempi kuin uusi arvo, tallennetaan uusi arvo*/
        temp = getHeight(pNode->pRight, current+1);
        h = (h >= temp) ? h : temp;

    }

    return h;

}


int searchKey(pTree pNode, int key) {                                           /*etsitään arvoa puusta*/

    if(pNode == NULL) {                                                         /*jos arvoa ei löydy puusta*/

        return 0;

    }

    else if(pNode->node == key) {                                               /*arvo on puussa*/

        return pNode->node;

    }

    else if(pNode->node > key) {                                                /*siirrytään vasemmalle, koska haettu arvo*/
                                                                                /*on pienempää kuin nykyisen solmun arvo*/
        return searchKey(pNode->pLeft, key);

    }

    else {                                                                      /*siirrytään oikealle, koska haettu arvo*/
                                                                                /*on suurempaa kuin nykyisen solmun arvo*/
        return searchKey(pNode->pRight, key);

    }

}

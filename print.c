
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include "bintree.h"
#include "misc.h"
#include <ctype.h>


int mainMenu(void) {

	int selection;
	char temp [3];

	printf ("Valitse toiminto valikosta:\n"
			"1) Lisää luku(ja) puuhun\n"
			"2) Tulosta puu\n"
			"3) Etsi luku\n"
			"4) Tyhjennä puu\n"
			"0) Lopeta\n"
			"Valintasi: ");

	fgets(temp, sizeof(temp), stdin);
	selection = atoi(temp);
	printf("\n");

	return selection;

}


int fileMenu(void) {

	char temp [3];

	while(1) {

		printf ("Valitse toiminto valikosta:\n"
				"1) Lue valmiista tiedostosta\n"
				"2) Luo uusi random-numerotiedosto\n"
				"Valintasi: ");
				fgets(temp, sizeof(temp), stdin);

				if(checkValue(*temp) == 1 && (atoi(temp) == 1 || atoi(temp) == 2)) {

					break;

				}

				else {

					printf("Virheellinen valinta!\n");

				}

		}

		return atoi(temp);

}


void printLines(int help, int height, int i) {

	for(int j = 0; (help-1)/2 > j; j++) {

		printf("\t");

	}

	if(i < height) {

		for(int k = 0; k < pow(2,i); k++) {

			printf("  %lc", 0x250F);

			for(int l = 0; l <= 4*help+1; l++) {

				printf("%lc", 0x2501);

			}

			printf("%lc", 0x253B);

			for(int l = 0; l <= 4*help+1; l++) {

				printf("%lc", 0x2501);

			}

			printf("%lc  ", 0x2513);

			for(int j = 0; help >= j; j++) {

				printf("\t");

			}

		}

	}

}


void printLayer(pTree pNode, int current, int layer, int h) {

    int i;
    int help = (int)pow(2.0, (double)(h-layer)) - 1;

    if(pNode && current == layer) {

        for(i = 0; help > i; i++) {

            printf("\t");

        }

        printf("%d[%d]\t\t", pNode->node, pNode->status);

        for(i = 0; help > i; i++) {

            printf("\t");

        }

    }

    else if(!pNode && current == layer) {

        for(i = 0; help > i; i++) {

            printf("\t");

        }

        printf("%s\t\t", "NULL");

        for(i = 0; help > i; i++) {

            printf("\t");

        }

    }


    else if(pNode && current < layer) {

        printLayer(pNode->pLeft, current+1, layer, h);
        //printf("\t%d %d\t", layer, h);
        printLayer(pNode->pRight, current+1, layer, h);

    }

    else if(!pNode && current < layer) {

        printf("\t\t\t\t");

    }

}


void printTree(pTree pStart) {

	setlocale(LC_ALL, "");
	int height = getHeight(pStart, 0), help;

	for(int i = 0; i <= height; i++) {

		help = (int)pow(2.0, (double)(height-i)) - 1;

		printLayer(pStart, 0, i, height);
		printf("\n");
		printLines(help, height, i);
		printf("\n\n");

	}

}

/*void printTree(pTree pNode, int i) {

    i++;

    if(pNode) {

        printTree(pNode->pRight, i);
        for(int j = 1; j < i; j++) {
            printf("\t");
        }

        printf("%d(%d)\n", pNode->node, pNode->status);
        printTree(pNode->pLeft, i);

    }

}*/

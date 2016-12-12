
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include <ctype.h>
#include <limits.h>
#include "bintree.h"
#include "misc.h"


int mainMenu(void) {															/*päävalikko*/

	int selection;
	char temp [CHAR_MAX/2];

	printf ("Valitse toiminto valikosta:\n"
			"1) Lisää luvut puuhun\n"
			"2) Tulosta puu\n"
			"3) Etsi luku\n"
			"4) Tyhjennä puu\n"
			"0) Lopeta\n"
			"Valintasi: ");

	fgets(temp, sizeof(temp), stdin);

	if(checkValue(*temp) == 1) {

		selection = atoi(temp);
		printf("\n");

	}

	else {

		selection = -1;

	}

	return selection;

}


int fileMenu(void) {															/*tiedostolukuvalikko*/

	char temp [CHAR_MAX/2];

	while(1) {

		printf ("Valitse toiminto valikosta:\n"
				"1) Lue valmiista tiedostosta\n"
				"2) Luo uusi random-numerotiedosto\n"
				"3) Lisää x peräkkäistä lukua\n"
				"Valintasi: ");
				fgets(temp, sizeof(temp), stdin);

				if(checkValue(*temp) == 1 && (atoi(temp) == 1 || atoi(temp) == 2 || atoi(temp) == 3)) {

					break;

				}

				else {

					printf("\nVirheellinen valinta!\n");

				}

		}

		return atoi(temp);

}


void printLines(int help, int height, int i, FILE *pFile) {						/*tulostaa muotoilun*/

	for(int j = 0; (help-1)/2 > j; j++) {

		fprintf(pFile, "\t");

	}

	if(i < height) {

		for(int k = 0; k < pow(2,i); k++) {

			fprintf(pFile, "  %lc", 0x250F);									/*oikea reuna*/

			for(int l = 0; l <= 4*help+1; l++) {								/*väliviiva*/

				fprintf(pFile, "%lc", 0x2501);

			}

			fprintf(pFile, "%lc", 0x253B);										/*keskimmäinen*/

			for(int l = 0; l <= 4*help+1; l++) {								/*väliviiva*/

				fprintf(pFile, "%lc", 0x2501);

			}

			fprintf(pFile, "%lc  ", 0x2513);									/*vasen reuna*/

			for(int j = 0; help >= j; j++) {

				fprintf(pFile, "\t");

			}

		}

	}

}


void printLayer(pTree pNode, int current, int layer, int h, FILE *pFile) {		/*kirjoitetaan tason solmut tiedostoon*/

    int i;
    int help = (int)pow(2.0, (double)(h-layer)) - 1;

    if(pNode && current == layer) {												/*jos ollaan halutulla tasolla ja solmu on olemassa*/

        for(i = 0; help > i; i++) {

            fprintf(pFile, "\t");

        }

        fprintf(pFile, "%d[%d]\t\t", pNode->node, pNode->status);

        for(i = 0; help > i; i++) {

            fprintf(pFile, "\t");

        }

    }

    else if(!pNode && current == layer) {										/*jos ollaan halutulla tasolla ja solmua ei ole olemassa*/

        for(i = 0; help > i; i++) {

            fprintf(pFile, "\t");

        }

        fprintf(pFile, "%s\t\t", "NULL");										/*tulostetaan solmun paikalle NULL*/

        for(i = 0; help > i; i++) {

            fprintf(pFile, "\t");

        }

    }


    else if(pNode && current < layer) {											/*siirrytään seuraavalle tasolle*/

        printLayer(pNode->pLeft, current+1, layer, h, pFile);
        //printf("\t%d %d\t", layer, h);
        printLayer(pNode->pRight, current+1, layer, h, pFile);

    }

    else if(!pNode && current < layer) {										/*jos ollaan jo tyhjässä*/

        fprintf(pFile, "\t\t\t\t");

    }

}


void printTree(pTree pStart) {													/*kirjoittaa puun muotoiltuna tiedostoon*/

	setlocale(LC_ALL, "");
	FILE* pFile;

	if((pFile = fopen("binääripuu.txt", "a")) == NULL) {

		perror("Tiedoston avaus epäonnistui\n");
		exit(1);

	}

	int height = getHeight(pStart, 0), help;

	for(int i = 0; i <= height; i++) {

		help = (int)pow(2.0, (double)(height-i)) - 1;							/*lasketaan tarvittavat tabulaattorit*/

		printLayer(pStart, 0, i, height, pFile);								/*printataan lukuarvot*/
		fprintf(pFile, "\n");
		printLines(help, height, i, pFile);										/*printataan puun muotoilu*/
		fprintf(pFile, "\n\n");

	}

	fprintf(pFile, "\n\n\n");
	fclose(pFile);

}


void printTreeTerminal(pTree pStart) {											/*lukee puutiedoston terminaaliin*/

	setlocale(LC_ALL, "");
	FILE* pFile;
	char buffer[CHAR_MAX/2];

	if((pFile = fopen("binääripuu.txt", "r")) == NULL) {

		perror("Tiedoston avaus epäonnistui\n");
		exit(1);

	}

	while(fgets(buffer,(sizeof(buffer)), pFile) != NULL) {

		printf("%s", buffer);

	}

	fclose(pFile);

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

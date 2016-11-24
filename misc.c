#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "bintree.h"

int checkValue(char);
void callTree(pTree *, int, int *);

void createTree(pTree *pStart, int stable) {												/*Aliohjelma tiedoston lukuun*/

	FILE* file;																	/*Määrittelyjä*/
	char buffer[CHAR_MAX];
	int j = 0;
	int number;

	if ((file = fopen("numbers.txt","r")) == NULL) {							/*Avatataan tiedosto lukutilaan*/

		perror("Tiedoston avaaminen epäonnistui");								/*Jos tiedoston avaaminen epäonnistuu*/
		exit(1);

	}

	printf("\n");
	while(fgets(buffer,(sizeof(buffer)), file) != NULL) {						/*Käydään tiedosto läpi rivi kerrallaan ja luetaan tiedot talteen*/

		j = j + 1;

		if ((checkValue(*buffer)) == 0) {

			number = atoi(buffer);
			callTree(pStart, number, &stable);

		}

		else {

			printf("Virhe rivillä %d.\n", j);									/*Ilmoitetaan, jos on virheellisiä rivejä*/

		}

	}

	if (j == 0) {																/*Jos tiedosto oli tyhjä*/

		printf("Tiedosto on tyhjä!\n");
		fclose(file);
		exit(1);

	}

	fclose(file);																/*Suljetaan tiedosto*/

}

int checkValue(char buffer) {

	int check1, check2;
    int check3 = 0;

	check1 = isalpha(buffer);
	check2 = isalnum(buffer);

	if(check1 != 0 && check2 != 0) {											/*jos merkki on kirjain*/

		check3 = 1;

	}

	else if (check1 == 0 && check2 != 0) {									    /*jos merkki on numero*/

		check3 = 0;

	}

	else if(buffer == '\0') {

		check3 = 1;

	}

	else {																		/*jos merkki on merkki*/

		check3 = 2;

	}

    if (check3 == 0) {                                                  	    /*palauttaa nollan jos numero*/

       return 0;

    }

    else if(check3 == 1) {                                                 		/*palauttaa ykkösen jos kirjaimia*/

        return 1;

    }

    else {                                                                      /*muussa tapauksessa*/

        return 2;

    }

}

void callTree(pTree *pStart, int number, int *stable) {

	int height;

	if(addNode(pStart, number, stable) == 0) {

		height = getHeight(*pStart, 0);
		printf("Puun syvyys: %d\n", height);

		printf("______________________________\n");

		for(int i = 0; i <= height; i++) {

			getLevels(*pStart, 0, i);
			printf("\n\n\n");

		}

		//printTree(*pStart, 0);
		printf("\n\n\n");

	}

}

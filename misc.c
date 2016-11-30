
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "bintree.h"
#include "print.h"
#include <locale.h>
#include <math.h>

int checkValue(char);


void callTree(pTree*, int, int *);


void generateNumbers(char *filename) {

	int minLimit, maxLimit, numCount, i, number;
	char tempMin[CHAR_MAX], tempMax[CHAR_MAX], tempCount[CHAR_MAX];
	FILE *pFile;

	while(1) {

		printf("Anna alaraja: ");
		fgets(tempMin, sizeof(tempMin), stdin);
		printf("Anna yläraja: ");
		fgets(tempMax, sizeof(tempMax), stdin);
		printf("Anna lukujen lukumäärä: ");
		fgets(tempCount, sizeof(tempCount), stdin);

		if(checkValue(*tempMin) == 1 && checkValue(*tempMax) == 1 && checkValue(*tempCount) == 1) {

			minLimit = atoi(tempMin);
			maxLimit = atoi(tempMax);
			numCount = atoi(tempCount);
			break;

		}

		else {

			printf("Virheellinen syöte :C\n");

		}

	}



	printf("Kirjoitetaan tiedostoon: %s\n", filename);
	if ((pFile = fopen(filename, "w")) != NULL) {

		for (i = 0; i < numCount; i++) {

			number = minLimit + rand() % (maxLimit-minLimit);
			fprintf(pFile,"%d\n", number);
			printf("%d ", number);

		}

	}

	else {

		perror("File writing failed.\n");
		exit(1);

	}

	fclose(pFile);
	printf("\n");


}


void createTree(pTree *pStart, int stable) {									/*Aliohjelma tiedoston lukuun*/

	FILE* file;																	/*Määrittelyjä*/
	char buffer[CHAR_MAX];
	char name[CHAR_MAX];
	int j = 0;
	int number, selection;

	selection = fileMenu();

	printf("Anna tiedoston nimi: ");
	fgets(name, sizeof(name), stdin);
	name[strlen(name) - 1] = '\0';

	if(selection == 2) {

		printf("Luodaan tiedosto: %s\n", name);
		generateNumbers(name);

	}

	printf("Avataan tiedosto: %s\n", name);
	if ((file = fopen(name,"r")) == NULL) {										/*Avatataan tiedosto lukutilaan*/

		perror("Tiedoston avaaminen epäonnistui");								/*Jos tiedoston avaaminen epäonnistuu*/
		exit(1);

	}

	printf("\n");
	while(fgets(buffer,(sizeof(buffer)), file) != NULL) {						/*Käydään tiedosto läpi rivi kerrallaan ja luetaan tiedot talteen*/

		j = j + 1;

		if ((checkValue(*buffer)) == 1) {

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

		check3 = 0;

	}

	else if (check1 == 0 && check2 != 0) {									    /*jos merkki on numero*/

		check3 = 1;

	}

	else if(buffer == '\0') {

		check3 = 0;

	}

	else {																		/*jos merkki on merkki*/

		check3 = 2;

	}

    if (check3 == 1) {                                                  	    /*palauttaa nollan jos numero*/

       return 1;

    }

    else if(check3 == 0) {                                                 		/*palauttaa ykkösen jos kirjaimia*/

        return 0;

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
		printTree(*pStart);
		printf("\n\n\n");

	}

}


/*short a = 0x2501;
wchar_t t = a;
printf("\nmerkki: %lc\n", t);*/

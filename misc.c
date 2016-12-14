
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
void callTree(pTree*, int, int, int *);


void generateNumbers(char *filename) {											/*generoidaan numeroita tiedostoon*/

	int minLimit, maxLimit, numCount, i, number;
	char tempMin[CHAR_MAX/2], tempMax[CHAR_MAX/2], tempCount[CHAR_MAX/2];
	FILE* pFile;

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

		perror("Tiedostoon kirjoittaminen epäonnistui.\n");
		exit(1);

	}

	fclose(pFile);
	printf("\n");


}


int generateX(char *filename) {

	int count, i;
	char tempC[CHAR_MAX/2];
	FILE* pFile;

	while(1) {

		printf("Kuinka monta lukua generoidaan: ");
		fgets(tempC, sizeof(tempC), stdin);

		if(checkValue(*tempC) == 1) {

			count = atoi(tempC);
			break;

		}

		else {

			printf("Virheellinen syöte :C\n");

		}

	}



	printf("Kirjoitetaan tiedostoon: %s\n", filename);
	if ((pFile = fopen(filename, "w")) != NULL) {

		for (i = 1; i <= count; i++) {

			fprintf(pFile,"%d\n", i);

		}

	}

	else {

		perror("Tiedostoon kirjoittaminen epäonnistui.\n");
		exit(1);

	}

	fclose(pFile);
	printf("\n");
	return count;

}


void createTree(pTree *pStart, int stable) {									/*Aliohjelma tiedoston lukuun*/

	FILE* pFile;
	char buffer[CHAR_MAX/2];
	char name[CHAR_MAX/2];
	int j = 0;
	int number, selection, check = 0;

	selection = fileMenu();

	if((pFile = fopen("binääripuu.txt", "w")) == NULL) {						/*avataan kirjoitus-tilassa jotta edellinen puu häviää*/

		perror("Tiedoston tyhjennys epäonnistui\n");
		exit(1);

	}

	fclose(pFile);

	printf("Anna tiedoston nimi: ");											/*avataan haluttu tiedosto*/
	fgets(name, sizeof(name), stdin);
	name[strlen(name) - 1] = '\0';

	if(selection == 2) {														/*luodaan tarvittaessa uusi numerotiedosto*/

		printf("Luodaan tiedosto: %s\n", name);
		generateNumbers(name);

	}

	else if(selection == 3) {

		printf("Luodaan tiedosto: %s\n", name);
		check = generateX(name);

	}

	printf("Avataan tiedosto: %s\n", name);
	if ((pFile = fopen(name,"r")) == NULL) {									/*Avatataan tiedosto lukutilaan*/

		perror("Tiedoston avaaminen epäonnistui");								/*Jos tiedoston avaaminen epäonnistuu*/
		return;

	}

	printf("\n");
	while(fgets(buffer,(sizeof(buffer)), pFile) != NULL) {						/*Käydään tiedosto läpi rivi kerrallaan ja luetaan tiedot talteen*/

		j = j + 1;

		if ((checkValue(*buffer)) == 1) {										/*tarkastetaan tiedostosta luetun arvon oikeellisuus*/

			number = atoi(buffer);
			callTree(pStart, number, check, &stable);							/*kutsutaan puuta*/

		}

		else {

			printf("Virhe rivillä %d.\n", j);									/*Ilmoitetaan, jos on virheellisiä rivejä*/

		}

	}

	if (j == 0) {																/*Jos tiedosto oli tyhjä*/

		printf("Tiedosto on tyhjä!\n");
		fclose(pFile);
		exit(1);

	}

	/*if(check != 0) {

		printTree(*pStart);

	}*/

	fclose(pFile);																/*Suljetaan tiedosto*/

}


int checkValue(char buffer) {													/*tarkastaa syötteen*/

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


void callTree(pTree *pStart, int number, int check, int *stable) {				/*kutsuu puuta*/

	int height;
	FILE* pFile;

	if(check == 0) {

		if((pFile = fopen("binääripuu.txt", "a")) == NULL) {

			perror("Tiedoston avaus epäonnistui\n");
			exit(1);

		}

		fprintf(pFile, "Lisätään luku: %d\n", number);
		height = getHeight(*pStart, 0);
		fprintf(pFile, "Puun syvyys: %d\n", height);
		fclose(pFile);

	}

	if(addNode(pStart, number, check, stable) == 0) {							/*jos puuhun lisäys onnistuu*/

		if(check == 0) {

			printTree(*pStart);													/*tulostetaan puu tiedostoon*/

		}

	}

}


/*short a = 0x2501;
wchar_t t = a;
printf("\nmerkki: %lc\n", t);*/

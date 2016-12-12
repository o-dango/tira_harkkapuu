#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "bintree.h"
#include "misc.h"
#include "print.h"

int main(void) {

	pTree pStart = NULL;
	char temp[CHAR_MAX/2];
	int selection = 1, key, stable = 0; /*stable = tasapainoilmaisin*/

	do {
		selection = mainMenu();													/*tulostetaan valikko*/

		switch (selection) {

			case 0:                     										/*Tyhjennys*/
			case 4:
				if (pStart != NULL) {
					emptyTree(pStart);
					pStart = NULL;

					printf("Muisti vapautettu!\n");
					printf("＼\\ ٩( ᐛ )و /／\n\n");

				}

				break;

			case 1:                     										/*Luvun lisäys*/
				if(pStart != NULL) {

					emptyTree(pStart);
					stable = 0;
					pStart = NULL;

				}

				createTree(&pStart, &stable);
				break;

			case 2:                     										/*Tulostus*/
				if (pStart == NULL) {

					printf("Puu on tyhjä!\n");
					break;

				}

				else if(getHeight(pStart, 0) > 4) {

					printf("Puu ei mahdu terminaaliin :(\n");
					break;

				}

				else {

					printTreeTerminal(pStart);
					printf("\n");
					break;

				}

			case 3:																/*Etsintä*/
				if(pStart == NULL) {

					printf("Puu on tyhjä!\n");
					break;

				}

				printf("Anna etsittävä luku: ");
				fgets(temp, sizeof(temp), stdin);

				if(checkValue(*temp) == 1) {

					key = searchKey(pStart, atoi(temp));

					if (key == 0) {
						printf("Lukua %d ei löytynyt puusta.\n", atoi(temp));

					} else {
						printf("%d löytyi binääripuusta.\n", key);

					}

				}

				else {

					printf("Virheellinen syöte :(\n");

				}

				printf("\n");
				break;

			default:															/*virheellinen syöte*/
				printf("\nVirheellinen valinta.\n");
				break;
		}

	} while (selection != 0);

	return 0;

}

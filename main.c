#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "bintree.h"
#include "misc.h"
#include "print.h"

int main(void) {

	pTree pStart = NULL;
	char temp[CHAR_MAX];
	int selection = 1, key, stable = 0; /*stable = tree balance indicator*/

	do {
		selection = mainMenu();

		switch (selection) {
			case 0:                     										/*Tyhjennys*/
			case 4:
				if (pStart != NULL) {
					emptyTree(pStart);
					pStart = NULL;
				}
				break;

			case 1:                     										/*Luvun lisäys*/

				createTree(&pStart, &stable);
				break;

			case 2:                     										/*Tulostus*/
				if (pStart == NULL) {
					printf("Puu on tyhjä!\n");
					break;
				}
				printTree(pStart);
				printf("\n");
				break;

			case 3:																/*Etsintä*/
				printf("Anna etsittävä luku: ");
				fgets(temp, sizeof(temp), stdin);

				if(checkValue(*temp) == 1) {

					key = searchKey(pStart, atoi(temp));

					if (key == 0) {
						printf("Lukua %d ei löytynyt puusta.\n", key);

					} else {
						printf("%d löytyi binääripuusta.\n", key);

					}

				}

				else {

					printf("Virheellinen syöte :(\n");

				}

				printf("\n");
				break;

			default:
				printf("Virheellinen valinta.\n");
				break;
		}
	} while (selection != 0);

	printf("\nMuisti vapautettu!\n");
	printf("＼\\ ٩( ᐛ )و /／\n");

	return 0;

}

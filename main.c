#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bintree.h"
#include "misc.h"

int main(void) {

	pTree pStart = NULL;
	int stable = 0;

	createTree(&pStart, &stable);
	printTree(pStart, 0);
	emptyTree(pStart);
	printf("\nMuisti vapautettu!\n");
	printf("＼\\ ٩( ᐛ )و /／\n");

	return 0;

}

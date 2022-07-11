#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mylib.h"

int main(int argc, char *argv[])
{
	int *A, *E, *O;
	int size, esize, osize;

	srand(time(NULL));

	size = atoi(argv[1]);

	A = (int*)malloc(sizeof(int) * size);
	E = (int*)malloc(sizeof(int) * size);
	O = (int*)malloc(sizeof(int) * size);

	fill_array(A, size);
	//print_array(A, size);

	A = realloc(A, sizeof(int) * (size+10));
	size += 10;

	fill_array_pos(A, size-10, size);
	//print_array(A, size);

	sort_array(A, size);
	//print_array(A, size);

	split_array(A, size, O, E, &esize);
	osize = size - esize;
	printf("%d %d %d\n", size, esize, osize);

	print_array(A, size);
	printf("\n");

	print_array(E, esize);
	print_array(O, osize);

	free(A);
	free(E);
	free(O);

    return 0;
}



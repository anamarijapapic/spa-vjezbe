#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
	int n, i = 0;
	int *arr;

	FILE* fp = fopen("..\\dodatno-zad1\\binaryfile.bin", "rb");
	if (fp == NULL) return 1;

	fread(&n, sizeof(int), 1, fp);
	printf("Number of array elements: n = %d\n", n);

	arr = (int*)malloc(n * sizeof(int));
	if (!arr) return NULL;

	while (fread(&arr[i++], sizeof(int), 1, fp));
	for (i = 0; i < n; i++) {
		printf("array[%d]: %d\n", i, arr[i]);
	}

	fclose(fp);

	free(arr);
	return 0;
}
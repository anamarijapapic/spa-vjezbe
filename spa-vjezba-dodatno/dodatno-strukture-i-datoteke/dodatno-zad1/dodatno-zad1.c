#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n, i;
	int *arr;

	FILE* fp = fopen("binaryfile.bin", "wb");
	if (fp == NULL) return 1;
	
	do {
		printf("How many numbers do you want to input to an array:\nn = ");
		scanf("%d", &n);
		if (n <= 0)
			printf("Invalid input!\n");
	} while (n <= 0);

	fwrite(&n, sizeof(int), 1, fp);

	arr = (int*)malloc(n * sizeof(int));
	if (!arr) return NULL;
	
	for (i = 0; i < n; i++) {
		printf("Enter array[%d]: ", i);
		scanf("%d", &arr[i]);
		fwrite(&arr[i], sizeof(int), 1, fp);
	}

	fclose(fp);

	free(arr);
	return 0;
}
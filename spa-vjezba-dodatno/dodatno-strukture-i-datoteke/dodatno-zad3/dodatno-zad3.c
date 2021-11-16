#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	float x;
	float y;
} Koordinata;

int main(void)
{
	unsigned n, i;
	Koordinata* array;
	FILE* fp = fopen("coordinates.bin", "wb");
	if (fp == NULL) return 1;
	
	do {
		printf("Enter the number of structures:\nn = ");
		scanf("%d", &n);
		if (n <= 0)
			printf("Invalid input!\n");
	} while (n <= 0);

	fwrite(&n, sizeof(int), 1, fp);

	array = (Koordinata*)malloc(n * sizeof(Koordinata));
	if (!array) return NULL;

	for (i = 0; i < n; i++) {
		printf("\n%d. structure:", i + 1);
		printf("\nEnter coordinates:\n");
		printf("x = ");
		scanf("%f", &array[i].x);
		fwrite(&array[i].x, sizeof(float), 1, fp);
		printf("y = ");
		scanf("%f", &array[i].y);
		fwrite(&array[i].y, sizeof(float), 1, fp);
	}

	fclose(fp);

	free(array);
	return 0;
}
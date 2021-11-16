#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	float x;
	float y;
} Koordinata;

int main(void)
{
	int n, index, i;
	Koordinata coordinate;

	FILE* fp = fopen("..\\dodatno-zad3\\coordinates.bin", "rb");
	if (fp == NULL) return 1;

	fread(&n, sizeof(int), 1, fp);

	do {
		printf("Enter index: ");
		scanf("%d", &index);
		if (index < 0 || index >= n)
			printf("Invalid input! That index does not exist.\n");
	} while (index < 0 || index >= n);

	fseek(fp, index * 8, SEEK_CUR);  // 8 = 2 * sizeof(float)
	fread(&coordinate.x, sizeof(float), 1, fp);
	fread(&coordinate.y, sizeof(float), 1, fp);
	printf("Coordinate on index %d is (%f, %f)", index, coordinate.x, coordinate.y);
	
	fclose(fp);
	return 0;
}
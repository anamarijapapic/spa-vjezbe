#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	float x;
	float y;
} Koordinata;

int main(void)
{
	int i, byteCount;
	Koordinata coordinate;
	FILE* fp = fopen("..\\dodatno-zad3\\coordinates.bin", "rb+");
	if (fp == NULL) return 1;

	fseek(fp, 0, SEEK_END);

	printf("Enter coordinates:\n");
	printf("x = ");
	scanf("%f", &coordinate.x);
	fwrite(&coordinate.x, sizeof(float), 1, fp);
	printf("y = ");
	scanf("%f", &coordinate.y);
	fwrite(&coordinate.y, sizeof(float), 1, fp);

	printf("\nAll coordinates in the file (printed backwards):\n");
	fseek(fp, 0, SEEK_END);
	byteCount = ftell(fp) - 4; // - 4 because the integer at the file start is excluded because it doesn't represent a coordinate point
	i = 0;
	while (i < byteCount) {
		i += 8;
		fseek(fp, -i, SEEK_END);
		fread(&coordinate.x, sizeof(float), 1, fp);
		fread(&coordinate.y, sizeof(float), 1, fp);
		printf("(%f, %f)\n", coordinate.x, coordinate.y);
	}

	fclose(fp);
	return 0;
}
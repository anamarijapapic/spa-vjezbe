#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void printArr(int arr[], int n)
{
	int i;
	for (i = 0; i < n; i++) {
		printf("%d  ", arr[i]);
	}
}

int* podniz(int* niz, int start, int stop)
{
	int i, j = 0;
	int* subArr = (int*)malloc(sizeof(int) * (stop - start + 1));
	if (!subArr) return NULL;
	for (i = start; i <= stop; i++, j++)
		subArr[j] = niz[i];
	return subArr;
}

int* filtriraj(int* niz, int n, int th, int* nth)
{
	int i, j = 0, cnt = 0;
	int* newArr;
	for (i = 0; i < n; i++) {
		if (niz[i] < th)
			cnt++;
	}
	*nth = cnt;
	newArr = (int*)malloc(sizeof(int) * cnt);
	if (!newArr) return NULL;
	for (i = 0; i < n; i++) {
		if (niz[i] < th) {
			newArr[j] = niz[i];
			j++;
		}
	}
	return newArr;
}

int** podijeli(int* niz, int n)
{
	int i, j = 0;
	int nArr1, nArr2;
	int* firstArr, * secondArr;
	int** pArr = (int**)malloc(sizeof(int*) * 2);
	if (!pArr) return NULL;
	nArr1 = n / 2;
	nArr2 = n - (n / 2);
	firstArr = (int*)malloc(sizeof(int) * (nArr1));
	if (!firstArr) return NULL;
	secondArr = (int*)malloc(sizeof(int) * (nArr2));
	if (!secondArr) return NULL;
	for (i = 0; i < n; i++) {
		if (i < nArr1)
			firstArr[i] = niz[i];
		else {
			secondArr[j] = niz[i];
			j++;
		}
	}
	pArr[0] = firstArr;
	pArr[1] = secondArr;
	return pArr;
}

typedef struct {
	float x;
	float y;
} Tocka;

typedef struct {
	Tocka* arrPoints;
	int n;
} Poligon;

Poligon* novi_poligon(float* niz_x, float* niz_y, int n)
{
	Poligon* polygon = ((Poligon*)malloc(sizeof(Poligon)));
	if (!polygon) return NULL;
	Tocka* arrPairs = ((Tocka*)malloc(sizeof(Tocka) * n));
	if (!arrPairs) return NULL;
	polygon->n = n;
	for (int i = 0; i < n; i++) {
		arrPairs[i].x = niz_x[i];
		arrPairs[i].y = niz_y[i];
	}
	polygon->arrPoints = arrPairs;
	return polygon;
}

Tocka** pozitivni(Poligon* p, int* np)
{
	Tocka** positivePoints;
	*np = 0;
	int i, j = 0;
	for (i = 0; i < p->n; i++) {
		if (p->arrPoints[i].x > 0 && p->arrPoints[i].y > 0) {
			(*np)++;
		}
	}
	positivePoints = (Tocka**)malloc(*np * sizeof(Tocka*));
	if (!positivePoints) return NULL;
	for (i = 0; i < p->n; i++) {
		if (p->arrPoints[i].x > 0 && p->arrPoints[i].y > 0) {
			positivePoints[j] = &(p->arrPoints[i]);
			j++;
		}
	}
	return positivePoints;
}

int main()
{
	int i;
	int arr[] = { 2, 4, 6, 8, 10, 12, 14, 16, 18, 20 };
	int* subArr, * newArr, ** pointerArr, * firstHalf, * secondHalf;
	int iStart = 2, iStop = 7;
	int th = 13;
	int nth = 0;
	int n = sizeof(arr) / sizeof(arr[0]);
	int n1, n2;
	float arr_x[] = {1, 4, 0.5, 10, 2, 2};
	float arr_y[] = {2, -3, 1, 5, 0, 1.25};
	int n_arr = 6;
	Poligon* polygon;
	Tocka** positivePoints;
	int np;

	printf("Original array:\n");
	printArr(arr, n);

	printf("\nSub-array:\n");
	subArr = podniz(arr, iStart, iStop);
	if (!subArr) return 1;
	printArr(subArr, iStop - iStart + 1);

	printf("\nArray with elements less than th = %d:\n", th);
	newArr = filtriraj(arr, n, th, &nth);
	if (!newArr) return 1;
	printArr(newArr, nth);

	pointerArr = podijeli(arr, n);
	if (!pointerArr) return 1;
	firstHalf = pointerArr[0];
	n1 = n / 2;
	printf("\nFirst half of array:\n");
	printArr(firstHalf, n1);
	secondHalf = pointerArr[1];
	n2 = n - (n / 2);
	printf("\nSecond half of array:\n");
	printArr(secondHalf, n2);

	polygon = novi_poligon(arr_x, arr_y, n_arr);
	if (!polygon) return 1;
	printf("\nPolygon points (x, y):");
	for (i = 0; i < n_arr; i++) {
		printf("\n(%.2f, %.2f)", polygon->arrPoints[i].x, polygon->arrPoints[i].y);
	}

	positivePoints = pozitivni(polygon, &np);
	if (!positivePoints) return 1;
	printf("\nThere is %d polygon points with both coordinates (x, y) positive.", np);
	printf("\nPositive polygon points (x, y):");
	for (i = 0; i < np; i++) {
		printf("\n(%.2f, %.2f)", positivePoints[i]->x, positivePoints[i]->y);
	}

	free(subArr);
	free(newArr);
	free(firstHalf);
	free(secondHalf);
	free(pointerArr);
	free(polygon);
	free(positivePoints);
	return 0;
}
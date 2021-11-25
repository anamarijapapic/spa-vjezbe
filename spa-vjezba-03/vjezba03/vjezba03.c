#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* generiraj(int n) 
{
    int* niz = (int*)malloc(sizeof(int) * n);
    niz[0] = rand() % 5;
    for (int i = 1; i < n; i++) {
        niz[i] = niz[i - 1] + 1 + rand() % 5;
    }
    return niz;
}

void shuffle(int* niz, int n) 
{
    for (int i = 0; i < n; i++) {
        int j = (rand() * rand()) % n;
        int tmp = niz[i];
        niz[i] = niz[j];
        niz[j] = tmp;
    }
}

int cmpfunc(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

int* presjek(int* skupA, int* skupB, int n)
{
    int k = 0;
    int* presjekAB = (int*)malloc(n * sizeof(int));
    if (!presjekAB) return NULL;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (skupA[i] == skupB[j]) {
                presjekAB[k] = skupA[i];
                k++;
            }
        }
    }
    presjekAB = (int*)realloc(presjekAB, k);
    return presjekAB;
}

int* presjek_jedan_sortiran(int* skupA, int* skupB, int n)
{
    int j = 0;
    int* presjekAB = (int*)malloc(n * sizeof(int));
    if (!presjekAB) return NULL;
    qsort(skupB, n, sizeof(int), cmpfunc);
    for (int i = 0; i < n; i++) {
        int* presjekItem = (int*)bsearch(&skupA[i], skupB, n, sizeof(int), cmpfunc);
        if (presjekItem) {
            presjekAB[j] = skupA[i];
            j++;
        }
    }
    presjekAB = (int*)realloc(presjekAB, j);
    return presjekAB;
}

int* presjek_oba_sortirana(int* skupA, int* skupB, int n)
{
    int i = 0, j = 0, k = 0;
    int* presjekAB = (int*)malloc(n * sizeof(int));
    if (!presjekAB) return NULL;
    qsort(skupA, n, sizeof(int), cmpfunc);
    qsort(skupB, n, sizeof(int), cmpfunc);
    while (i < n && j < n) {
        if (skupA[i] == skupB[j]) {
            presjekAB[k] = skupA[i];
            i++, j++, k++;
        }
        else if (skupA[i] > skupB[j]) {
            j++;
        }
        else {
            i++;
        }
    }
    presjekAB = (int*)realloc(presjekAB, k);
    return presjekAB;
}

void main()
{
    srand(time(NULL));

    clock_t elapsed_time;
    int n;

    /*do {
        printf("Please enter array size for sets A and B: ");
        scanf("%d", &n);
        if (n <= 0)
            printf("Invalid input! Array size must be larger than 0!\n");
    } while (n <= 0);*/

    // algorithm execution time measurement - both sets unsorted 
    /*for (n = 10000; n <= 200000; n += 10000) {
        printf("\nArray size: %d\n", n);
        int* skupA = generiraj(n);
        shuffle(skupA, n);
        int* skupB = generiraj(n);
        shuffle(skupB, n);

        elapsed_time = clock();
        int* presjekAB_1 = presjek(skupA, skupB, n);
        free(presjekAB_1);
        elapsed_time = clock() - elapsed_time;
        printf("\nIntersection of A and B (both unsorted):\nElapsed time in seconds: %lf\n", (double)elapsed_time / CLOCKS_PER_SEC);
    }*/

    for (n = 500000; n <= 10000000; n += 500000) {
        printf("\nArray size: %d\n", n);
        int* skupA = generiraj(n);
        shuffle(skupA, n);
        int* skupB = generiraj(n);
        shuffle(skupB, n);

        // algorithm execution time measurement - first set unsorted (A), second set sorted using qsort (B) - intersect found using bsearch
        elapsed_time = clock();
        int* presjekAB_2 = presjek_jedan_sortiran(skupA, skupB, n);
        free(presjekAB_2);
        elapsed_time = clock() - elapsed_time;
        printf("\nIntersection of A and B (A unsorted, B sorted):\nElapsed time in seconds: %lf\n", (double)elapsed_time / CLOCKS_PER_SEC);

        // algorithm execution time measurement - both sets sorted using qsort
        elapsed_time = clock();
        int* presjekAB_3 = presjek_oba_sortirana(skupA, skupB, n);
        free(presjekAB_3);
        elapsed_time = clock() - elapsed_time;
        printf("\nIntersection of A and B (both sorted):\nElapsed time in seconds: %lf\n", (double)elapsed_time / CLOCKS_PER_SEC);
    }
}
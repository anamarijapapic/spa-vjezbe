#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define LEN 10000

typedef struct
{
	void* data;
	int priority;
} Leaf;

typedef struct
{
	Leaf* array;
	int number;
} Heap;

/*
r -> roditelj (parent)
c -> dijete (child)
l -> lijevo (left)
d -> desno (right)
*/

Heap* create()
{
	Heap* queue = (Heap*)malloc(sizeof(Heap));
	if (queue == NULL)
		return NULL;
	queue->array = (Leaf*)malloc(LEN * sizeof(Leaf));
	if (queue->array == NULL)
		return NULL;
	queue->number = 0;
	return queue;
}

void destroy(Heap* h)
{
	free(h->array);
	free(h);
}

void fix_to_top(Heap* h, int c)
{
	int r = (c - 1) / 2;
	if (c == 0)
		return;
	if (h->array[r].priority < h->array[c].priority)
	{
		int tmp = h->array[r].priority;
		h->array[r].priority = h->array[c].priority;
		h->array[c].priority = tmp;
		fix_to_top(h, r);
	}
}

void add(Heap* h, int element)
{
	h->array[h->number].priority = element;
	fix_to_top(h, h->number);
	h->number++;
}

void fix_to_bottom(Heap* h, int r)
{
	int l = 2 * r + 1;
	int d = 2 * r + 2;

	if (l >= h->number && d >= h->number)
		return;
	else
	{
		if (h->array[r].priority < h->array[l].priority || h->array[r].priority < h->array[d].priority)
		{
			if (h->array[l].priority > h->array[d].priority)
			{
				int tmp = h->array[l].priority;
				h->array[l].priority = h->array[r].priority;
				h->array[r].priority = tmp;
				fix_to_bottom(h, l);
			}
			else if (h->array[d].priority > h->array[l].priority)
			{
				int tmp = h->array[r].priority;
				h->array[r].priority = h->array[d].priority;
				h->array[d].priority = tmp;
				fix_to_bottom(h, d);
			}
		}
	}
}

void remove_leaf(Heap* h)
{
	int tmp = h->array[h->number - 1].priority;
	h->array[0].priority = tmp;
	h->number--;
	fix_to_bottom(h, 0);
}

// Dodatno:

void swap_elements(int *arr, int i, int j) {
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void heapify(int *arr, int i, int m) {
	int j;
	while (2 * i + 1 <= m) {
		j = 2 * i + 1;
		if (j < m) {
			if (arr[j] < arr[j + 1])
				j++;
		}
		if (arr[i] < arr[j]) {
			swap_elements(arr, i, j);
			i = j;
		}
		else
			i = m;
	}
}

void heapsort(int* arr, int n) {
	if (n == 0)
		return;
	for (int i = (n - 2) / 2; i >= 0; i--)
		heapify(arr, i, n - 1);
	for (int i = n - 1; i > 0; i--) {
		swap_elements(arr, 0, i);
		heapify(arr, 0, i - 1);
	}
}

void main()
{
	Heap* queue = create();

	add(queue, 1);
	add(queue, 2);
	add(queue, 3);
	add(queue, 4);
	add(queue, 5);
	add(queue, 6);
	add(queue, 7);
	add(queue, 8);
	add(queue, 9);
	add(queue, 10);
	add(queue, 11);

	remove_leaf(queue);

	for (int i = 0; i < queue->number; i++)
		printf("%d  ", queue->array[i].priority);

	puts("");

	destroy(queue);

	// Dodatno:

	int array[] = { 8, 6, 2, 5, 3, 7, 1, 9, 4, 10 };
	int n = 10;

	heapsort(array, n);
	
	for (int i = 0; i < n; i++) {
		printf("%d  ", array[i]);
	}
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "longnumber.h"

LongNumber reverse(LongNumber num)
{
	LongNumber lst = NULL;

	while (num != NULL) {
		LongNumber tmp = (LongNumber)malloc(sizeof(Digit));
		if (!tmp)
			return NULL;
		tmp->z = num->z;
		tmp->next = lst;
		lst = tmp;
		num = num->next;
	}

	return lst;
}

LongNumber read_longnum(char* fname)
{
	FILE* fp = fopen(fname, "r");
	if (!fp) {
		printf("Error opening file.\n");
		return NULL;
	}

	char c;
	LongNumber lst = NULL;

	while ((c = fgetc(fp)) != EOF) {
		LongNumber tmp = (LongNumber)malloc(sizeof(Digit));
		if (!tmp)
			return NULL;
		tmp->z = c - '0';
		tmp->next = lst;
		lst = tmp;
	}

	lst = reverse(lst);

	return lst;
}

void write_longnum(LongNumber num, char* fname)
{
	FILE* fp = fopen(fname, "a+");
	if (!fp) {
		printf("Error opening file.\n");
		return;
	}

	while (num != NULL) {
		fprintf(fp, "%d", num->z);
		num = num->next;
	}
	fprintf(fp, "\n");
}

void print_longnum(LongNumber num)
{
	while (num != NULL) {
		printf("%d", num->z);
		num = num->next;
	}
	printf("\n");
}

void delete_longnum(LongNumber num)
{
	LongNumber tmp = NULL;

	while (num != NULL) {
		tmp = num;
		num = num->next;
		free(tmp);
	}
}

LongNumber add_longnum(LongNumber a, LongNumber b)
{
	a = reverse(a);
	b = reverse(b);

	LongNumber lst = NULL;

	int remainder = 0;
	int sum = 0;
	int tmpA, tmpB;

	while (a || b || remainder) {
		if (a != NULL) {
			tmpA = a->z;
			a = a->next;
		}
		else {
			tmpA = 0;
		}

		if (b != NULL) {
			tmpB = b->z;
			b = b->next;
		}
		else {
			tmpB = 0;
		}

		sum = tmpA + tmpB + remainder;
		
		LongNumber tmp = (LongNumber)malloc(sizeof(Digit));
		if (!tmp)
			return NULL;
		
		if (sum > 9) {
			tmp->z = sum % 10;
		}
		else {
			tmp->z = sum;
		}

		remainder = sum / 10;
		tmp->next = lst;
		lst = tmp;
	}

	return lst;
}

LongNumber mul_by_digit(LongNumber num, int z)
{
	num = reverse(num);

	LongNumber lst = NULL;

	int remainder = 0;

	while (num != NULL) {
		LongNumber tmp = (LongNumber)malloc(sizeof(Digit));
		if (!tmp)
			return NULL;
		int prod = num->z * z + remainder;
		tmp->z = prod % 10;
		remainder = prod / 10;
		tmp->next = lst;
		lst = tmp;
		num = num->next;
	}

	if (remainder > 0) {
		LongNumber tmp = (LongNumber)malloc(sizeof(Digit));
		if (!tmp)
			return NULL;
		tmp->z = remainder;
		tmp->next = lst;
		lst = tmp;
	}
	return lst;
}

LongNumber mul_by_pow10(LongNumber num, int pow)
{
	if (!pow)
		return num;

	num = reverse(num);

	LongNumber lst = NULL;

	while (pow > 0) {
		LongNumber tmp = (LongNumber)malloc(sizeof(Digit));
		if (!tmp)
			return NULL;
		tmp->z = 0;
		tmp->next = lst;
		lst = tmp;
		pow--;
	}

	while (num != NULL) {
		LongNumber tmp = (LongNumber)malloc(sizeof(Digit));
		if (!tmp)
			return NULL;
		tmp->z = num->z;
		tmp->next = lst;
		lst = tmp;
		num = num->next;
	}

	return lst;
}

LongNumber mul_longnum(LongNumber a, LongNumber b)
{
	b = reverse(b);

	LongNumber lst = NULL;

	int pow = 0;

	while (b != NULL) {
		LongNumber tmp = (LongNumber)malloc(sizeof(Digit));

		tmp = mul_by_digit(a, b->z);
		tmp = mul_by_pow10(tmp, pow);

		if (lst != NULL) {
			lst = add_longnum(lst, tmp);
		}
		else {
			lst = tmp;
		}

		pow++;

		b = b->next;
	}

	return lst;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int mystrlen(char* str)
{
	int len = 0;
	while (*(str + len) != '\0') {
		len++;
	}
	return len;
}

char* mystrcpy(char* destination, char* source)
{
	int i;
	for (i = 0; source[i] != '\0'; i++)
		destination[i] = source[i];
	destination[i] = '\0';
	return destination;
}

int mystrcmp(char* str1, char* str2)
{
	int i = 0;
	while (str1[i] == str2[i]) {
		if (str1[i] == '\0' && str2[i] == '\0')
			return 0;
		i++;
	}
	if (str1[i] > str2[i])
		return 1;
	else
		return -1;
}

char* mystrcat(char* destination, char* source)
{
	int i = 0;
	int start = mystrlen(destination);
	while (source[i] != '\0') {
		destination[start + i] = source[i];
		i++;
	}
	destination[start + i] = '\0';
	return destination;
}

char* mystrstr(char* str, char* substr)
{
	int i = 0, j;
	while (str[i] != '\0') {
		j = 0;
		while (str[i + j] == substr[j]) {
			j++;
			if (substr[j] == '\0')
				return &str[i];
		}
		i++;
	}
	return NULL;
}

char* reverse(char* destination, char* source)
{
	int i;
	int j = mystrlen(source) - 1;
	for (i = 0; source[i] != '\0'; i++, j--)
		destination[i] = source[j];
	destination[i] = '\0';
	return destination;
}

void main()
{
	char* p;
	char* q;
	char str1[20] = "Hello World!";
	char str2[50] = "";
	printf("str1: %s\nstr2: %s\n", str1, str2);
	printf("\nmystrlen(str1): %d\nstrlen(str1): %d\n", mystrlen(str1), strlen(str1));
	printf("\nmystrcpy(str2, str1): %s", mystrcpy(str2, str1));
	printf("\nstrcpy(str2, str1): %s\n", strcpy(str2, str1));
	printf("\nmystrcmp(str1, str2): %d\nstrcmp(str1, str2): %d\n", mystrcmp(str1, str2), strcmp(str1, str2));
	printf("\nmystrcat(str2, str1): %s", mystrcat(str2, str1));
	printf("\nstrcat(str2, str1): % s\n", strcat(str2, str1));
	p = mystrstr("abaaaaabaa", "aaab");
	q = strstr("abaaaaabaa", "aaab");
	if (p != NULL) {
		printf("\nmystrstr('abaaaaabaa', 'aaab'): %p, %c", p, *p);
	}
	if (q != NULL) {
		printf("\nstrstr('abaaaaabaa', 'aaab'): %p, %c", q, *q);
	}
	printf("\n\nreverse(str2, str1): %s", reverse(str2, str1));
}
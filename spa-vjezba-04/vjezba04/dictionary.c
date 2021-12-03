#define _CRT_SECURE_NO_WARNINGS
#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// kreira new_dict prazni rjecnik
Dictionary create()
{
	Dictionary dict = (Dictionary)malloc(sizeof(Word));
	if (!dict) return NULL;
	dict->count = 0;
	dict->word = NULL;
	dict->next = NULL;
	return dict;
}

// dodaje rijec ili uvecava broj pojavljivanja rijeci u rjecniku
// rijeci se dodaju u abecednom redu
void add(Dictionary dict, char* str)
{
	Dictionary p = dict;
	Dictionary n = dict->next;

	Dictionary new_dict = (Dictionary)malloc(sizeof(Word));
	if (!new_dict) return;
	new_dict->word = (char*)malloc(sizeof(char) * (strlen(str) + 1));
	if (!new_dict->word) return;
	strcpy(new_dict->word, str);
	new_dict->count = 1;

	while (n != NULL) {
		if (strcmp(n->word, str) == 0) {
			n->count++;
			free(new_dict->word);
			free(new_dict);
			return;
		}
		else if (strcmp(n->word, str) > 0) {
			new_dict->next = n;
			p->next = new_dict;
			return;
		}
		p = p->next;
		n = n->next;
	}
	p->next = new_dict;
	new_dict->next = NULL;
}

// ispisuje sve rijeci i broj pojavljivanja svake rijeci
void print(Dictionary dict)
{
	dict = dict->next;
	while (dict != NULL) {
		printf("%s -> %d\n", dict->word, dict->count);
		dict = dict->next;
	}
	printf("\n");
}

// brise cijeli rjecnik
void destroy(Dictionary dict)
{
	Dictionary tmp = dict;
	dict = dict->next;
	free(tmp);

	while (dict != NULL) {
		tmp = dict;
		dict = dict->next;
		free(tmp->word);
		free(tmp);
	}
}

// vraca 1 ako je broj pojavljivanja rijeci izmedju 5 i 10 i ako je rijec duza od 3 znaka
int filter(Word* w)
{
	if ((w->count > 5 && w->count < 10) && strlen(w->word) > 3)
		return 1;
	return 0;
}

// funkcija za filtriranje liste
// prima rjecnik (lista ispunjena sa abecedno poredanim rijecima i brojem pojavljivanja u tekstu) i pokazivac na funkciju int filter(Word *w)
// vraca izmijenjenu indict listu koja sadrzi samo rijeci za koje je filter() funkcija vratila 1 (sve druge rijeci se oslobadjaju)
Dictionary filterDictionary(Dictionary indict, int (*filter)(Word* w))
{
	Dictionary p = indict;
	Dictionary n = indict->next;

	while (n != NULL) {
		if (!filter(n)) {
			p->next = n->next;
			free(n->word);
			free(n);
			n = p->next;
		}
		else {
			p = p->next;
			n = n->next;
		}
	}

	return indict;
}
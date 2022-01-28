#include "hash.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>

#define HCONST 3567892

HashTable* NewTable(int size)
{
	// kreira novu hash tablicu (alocira samu strukturu i niz pokazivaca)
	HashTable* dict = (HashTable*)malloc(sizeof(HashTable));
	if (!dict) return NULL;
	dict->table = ((Bin**)malloc(sizeof(Bin*) * size));
	if (!dict->table) return NULL;
	dict->size = size;
	dict->load = 0;
	for (int i = 0; i < size; i++) {
		dict->table[i] = NULL;
	}
	return dict;
}

unsigned int hash(char* word)
{
	// od kljuca generira hash kod
	unsigned int key = 0;
	while (*word != '\0')
	{
		key = key * HCONST + *word;
		word++;
	}
	return key;
}

void Insert(HashTable* ht, char* word)
{
	// dodaje novu rijec u listu na odgovarajucem pretincu
	unsigned int key = hash(word) % ht->size;
	ht->load++;
	Bin* tmp = (Bin*)malloc(sizeof(Bin));
	if (!tmp) return;
	tmp->word = word;
	tmp->next = ht->table[key];
	ht->table[key] = tmp;
}

int Get(HashTable* ht, char* word)
{
	// vraca 0 ili 1 ovisno o tome da li rijec postoji u tablici
	unsigned int key = hash(word) % ht->size;
	while (ht->table[key] != NULL) {
		if (!strcmp(ht->table[key]->word, word)) {
			return 1;
		}
		ht->table[key] = ht->table[key]->next;
	}
	return 0;
}

void DeleteTable(HashTable* ht)
{
	// brise cijelu hash tablicu (liste na svim pretincima (rijec i element liste), pretince ...)
	for (int i = 0; i < ht->size; i++) {
		while (ht->table[i] != NULL) {
			Bin* tmp = ht->table[i];
			ht->table[i] = ht->table[i]->next;
			free(tmp->word);
			free(tmp);
		}
	}
	free(ht->table);
	free(ht);
}
#ifndef DICTIONARY_H
#define DICTIONARY_H

typedef struct Word {
	char* word; // rijec
	int count; // broj pojavljivanja rijeci
	struct Word* next;
} Word;

typedef Word* Dictionary;

// kreira novi prazni rjecnik
Dictionary create();

// dodaje rijec ili uvecava broj pojavljivanja rijeci u rjecniku
// rijeci se dodaju u abecednom redu
void add(Dictionary dict, char* str);

// ispisuje sve rijeci i broj pojavljivanja svake rijeci
void print(Dictionary dict);

// brise cijeli rjecnik
void destroy(Dictionary dict);

// vraca 1 ako je broj pojavljivanja rijeci izmedju 5 i 10 i ako je rijec duza od 3 znaka
int filter(Word* w);

// funkcija za filtriranje liste
// prima rjecnik (lista ispunjena sa abecedno poredanim rijecima i brojem pojavljivanja u tekstu) i pokazivac na funkciju int filter(Word *w)
// vraca izmijenjenu indict listu koja sadrzi samo rijeci za koje je filter() funkcija vratila 1 (sve druge rijeci se oslobadjaju)
Dictionary filterDictionary(Dictionary indict, int (*filter)(Word* w));

#endif
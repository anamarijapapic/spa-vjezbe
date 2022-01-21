#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <malloc.h>
#include "bstree.h"

BSTree NewBSTree()
{
	// Novo prazno stablo
	return NULL;
}

void CreateNode(BSTree* bst, char* word)
{
	*bst = (BSTree)malloc(sizeof(Node));
	if (!*bst) return NULL;
	(*bst)->left = NULL;
	(*bst)->right = NULL;
	(*bst)->word = word;
}

void AddNode(BSTree *bst, char *word)
{
	// Rekurzivno se trazi mjesto za novi cvor u stablu. Ako rijec postoji u stablu, ne dodaje se.
	// bst parametar je dvostruki pokazivac.
	if (*bst == NULL)
		CreateNode(bst, word);
	else if (strcmp((*bst)->word, word) > 0)
		AddNode(&(*bst)->left, word);
	else if (strcmp((*bst)->word, word) < 0)
		AddNode(&(*bst)->right, word);
	else
		free(word);
}

int BSTHeight(BSTree bst)
{
	// Rekurzivno se prolazi cijelo stablo da bi se pronasla najduza grana (visina stabla).
	if (bst == NULL)
		return 0;
	int left_depth = BSTHeight(bst->left);
	int right_depth = BSTHeight(bst->right);
	if (left_depth > right_depth)
		return left_depth + 1;
	else
		return right_depth + 1;
}

void PrintBSTree(BSTree bst)
{
	// Ispisuje rijeci u stablu na ekran po abecednom redu.
	// In-order setnja po stablu (lijevo dijete, cvor, desno dijete)
	if (bst == NULL)
		return;
	PrintBSTree(bst->left);
	puts(bst->word);
	PrintBSTree(bst->right);
}

void SaveBSTree(BSTree bst, FILE *fd)
{
	// Snima rijec po rijec iz stabla u tekstualnu datoteku. Rijeci su odvojene razmakom.
	// Pre-order setnja po stablu (trenutni cvor pa djeca)
	if (bst == NULL)
		return;
	fprintf(fd, "%s\n", bst->word);
	SaveBSTree(bst->left, fd);
	SaveBSTree(bst->right, fd);
}

void DeleteBSTree(BSTree bst)
{
	// Brise stablo (string word i sam cvor) iz memorije.
	// Post-order setnja po stablu (prvo djeca pa trenutni cvor)
	if (bst == NULL)
		return;
	DeleteBSTree(bst->left);
	DeleteBSTree(bst->right);
	free(bst->word);
	free(bst);
}

BSTree LoadBSTree(FILE *fd)
{
	// Ucitava rijec po rijec iz tekstualne datoteke i dodaje ih u stablo preko AddNode() funkcije.
	// Rijec duplicirati sa strdup().
	char* buffer[1024];
	BSTree bst = NewBSTree();
	while (fgets(buffer, 1024, fd) != NULL)
		AddNode(&bst, strdup(buffer));
	return bst;
}
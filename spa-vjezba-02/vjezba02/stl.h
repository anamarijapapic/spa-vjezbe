#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	float x, y, z;
} Vrh;

typedef struct {
	Vrh normala; // ni nj nk
	Vrh vrhovi[3];
	// v1x v1y v1z
	// v2x v2y v2z
	// v3x v3y v3z
	unsigned short boja;
} Trokut;

typedef struct {
	Trokut* nizTrokuta;
	unsigned int n;
} Objekt3D;

Objekt3D* citaj_binarnu_STL(FILE* fp);
Objekt3D* citaj_tekstualnu_STL(FILE* fp);
void zapisi_u_binarnu_STL(FILE* fp, Objekt3D* objekt);
void zapisi_u_tekstualnu_STL(FILE* fp, Objekt3D* objekt);
void obrisi_Objekt3D_strukturu(Objekt3D* objekt);
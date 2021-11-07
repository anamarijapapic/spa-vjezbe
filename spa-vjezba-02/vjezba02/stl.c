#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stl.h"

Objekt3D* citaj_binarnu_STL(FILE* fp)
{
	int i = 0;
	Objekt3D* objekt = (Objekt3D*)malloc(sizeof(Objekt3D));
	if (!objekt) return NULL;
	fseek(fp, 80, SEEK_SET); // postavljanje pokazivaca u datoteci tako da "preskocimo" zaglavlje
	fread(&(objekt->n), sizeof(unsigned int), 1, fp); // citanje ukupnog broja trokuta iz datoteke
	objekt->nizTrokuta = (Trokut*)malloc(objekt->n * sizeof(Trokut));
	if (!objekt->nizTrokuta) return NULL;
	while (fread(&(objekt->nizTrokuta[i++]), 50, 1, fp)); // citanje niza trokuta (zauzima 50 bajtova) iz datoteke
	return objekt;
}

Objekt3D* citaj_tekstualnu_STL(FILE* fp)
{
	unsigned int i = 0, j = 0;
	unsigned int cnt = 0;
	char buffer[255];

	Objekt3D* objekt = (Objekt3D*)malloc(sizeof(Objekt3D));
	if (!objekt) return NULL;
	fgets(buffer, 255, fp); // cita prvu liniju "solid 'ime'"
	int after_solid_ime = ftell(fp); // pamti poziciju nakon prve linije
	// brojanje koliko ima trokuta - svaki trokut zavrsava linijom "  endfacet"
	while (fscanf(fp, "%s", buffer) != EOF) {
		if (strcmp(buffer, "endfacet") == 0) {
			cnt++;
		}
	}
	objekt->n = cnt; // pridruzivanje ukupnog broja trokuta strukturi
	objekt->nizTrokuta = (Trokut*)malloc(objekt->n * sizeof(Trokut));
	if (!objekt->nizTrokuta) return NULL;
	fseek(fp, after_solid_ime, SEEK_SET); // pozicioniranje iza prve linije
	while (fscanf(fp, "%s", buffer) != EOF) {
		// cita normalu - %*s ignorira input do whitespacea ili newlinea
		while (fscanf(fp, "%*s %f %f %f\n", &objekt->nizTrokuta[i].normala.x, &objekt->nizTrokuta[i].normala.y, &objekt->nizTrokuta[i].normala.z) == 1);
		fgets(buffer, 255, fp); // cita liniju "    outer loop"
		for (j = 0; j < 3; j++) {
			// cita koordinate vrhova trokuta - %*s ignorira input do whitespacea ili newlinea
			while (fscanf(fp, " %*s %f %f %f\n", &objekt->nizTrokuta[i].vrhovi[j].x, &objekt->nizTrokuta[i].vrhovi[j].y, &objekt->nizTrokuta[i].vrhovi[j].z) == 1);
		}
		fgets(buffer, 255, fp); // cita liniju "    endloop"
		fgets(buffer, 255, fp); // cita liniju "  endfacet"
		i++;
	}

	return objekt;
}

void zapisi_u_binarnu_STL(FILE* fp, Objekt3D* objekt)
{
	unsigned int i, j;
	char buffer[80] = { 0 };
	fwrite(buffer, 1, 80, fp); // zaglavlje od 80 bajtova ispunjeno nulama
	fwrite(&(objekt->n), sizeof(unsigned int), 1, fp); // upisivanje ukupnog broja trokuta
	for (i = 0; i < objekt->n; i++) {
		// upisivanje normale
		fwrite(&objekt->nizTrokuta[i].normala.x, sizeof(float), 1, fp);
		fwrite(&objekt->nizTrokuta[i].normala.y, sizeof(float), 1, fp);
		fwrite(&objekt->nizTrokuta[i].normala.z, sizeof(float), 1, fp);
		// upisivanje koordinata vrhova trokuta
		for (j = 0; j < 3; j++) {
			fwrite(&objekt->nizTrokuta[i].vrhovi[j].x, sizeof(float), 1, fp);
			fwrite(&objekt->nizTrokuta[i].vrhovi[j].y, sizeof(float), 1, fp);
			fwrite(&objekt->nizTrokuta[i].vrhovi[j].z, sizeof(float), 1, fp);
		}
		fwrite(&objekt->nizTrokuta[i].boja, sizeof(unsigned short), 1, fp); // upisivanje boje
	}
}

void zapisi_u_tekstualnu_STL(FILE* fp, Objekt3D* objekt)
{
	unsigned int i, j;
	char ime[] = "OpenSCAD_Model";
	fprintf(fp, "solid %s\n", ime);
	for (i = 0; i < objekt->n; i++) {
		fprintf(fp, "  facet normal %f %f %f\n", objekt->nizTrokuta[i].normala.x, objekt->nizTrokuta[i].normala.y, objekt->nizTrokuta[i].normala.z);
		fprintf(fp, "    outer loop\n");
		for (j = 0; j < 3; j++) {
			fprintf(fp, "      vertex %f %f %f\n", objekt->nizTrokuta[i].vrhovi[j].x, objekt->nizTrokuta[i].vrhovi[j].y, objekt->nizTrokuta[i].vrhovi[j].z);
		}
		fprintf(fp, "    endloop\n");
		fprintf(fp, "  endfacet\n");
	}
	fprintf(fp, "endsolid %s", ime);
}

void obrisi_Objekt3D_strukturu(Objekt3D* objekt)
{
	if (objekt != NULL) {
		free(objekt->nizTrokuta);
		free(objekt);
	}
}
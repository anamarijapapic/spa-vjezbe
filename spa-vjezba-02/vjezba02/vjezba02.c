#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "stl.h"

// Free online STL Viewer: https://www.viewstl.com/

int main()
{
	FILE* fp1;
	FILE* fp2;
	FILE* fp3;
	FILE* fp4;
	FILE* fp5;
	FILE* fp6;
	Objekt3D* objektbin;
	Objekt3D* objekttxt;

	/*ZA OBJEKT3D STRUKTURU objektbin ISPUNJENU CITANJEM BINARNE STL DATOTEKE*/
	
	// cita binarnu STL datoteku i vraca ispunjenu Objekt3D strukturu
	fp1 = fopen("primjerbin.stl", "rb");
	if (fp1 == NULL) return 1;
	objektbin = citaj_binarnu_STL(fp1);
	fclose(fp1);

	// Objekt3D strukturu zapisuje u binarnu STL datoteku
	fp2 = fopen("objektbin_datotekabin.stl", "wb");
	if (fp2 == NULL) return 1;
	zapisi_u_binarnu_STL(fp2, objektbin);
	fclose(fp2);

	// Objekt3D strukturu zapisuje u tekstualnu STL datoteku
	fp3 = fopen("objektbin_datotekatxt.stl", "wt");
	if (fp3 == NULL) return 1;
	zapisi_u_tekstualnu_STL(fp3, objektbin);
	fclose(fp3);

	// brise Objekt3D strukturu
	obrisi_Objekt3D_strukturu(objektbin);

	/*ZA OBJEKT3D STRUKTURU objekttxt ISPUNJENU CITANJEM TEKSTUALNE STL DATOTEKE*/

	// cita tekstualnu STL datoteku i vraca ispunjenu Objekt3D strukturu
	fp4 = fopen("primjertxt.stl", "rt");
	if (fp4 == NULL) return 1;
	objekttxt = citaj_tekstualnu_STL(fp4);
	fclose(fp4);

	// Objekt3D strukturu zapisuje u binarnu STL datoteku
	fp5 = fopen("objekttxt_datotekabin.stl", "wb");
	if (fp5 == NULL) return 1;
	zapisi_u_binarnu_STL(fp5, objekttxt);
	fclose(fp5);

	// Objekt3D strukturu zapisuje u tekstualnu STL datoteku
	fp6 = fopen("objekttxt_datotekatxt.stl", "wt");
	if (fp6 == NULL) return 1;
	zapisi_u_tekstualnu_STL(fp6, objekttxt);
	fclose(fp6);

	// brise Objekt3D strukturu
	obrisi_Objekt3D_strukturu(objekttxt);

	return 0;
}
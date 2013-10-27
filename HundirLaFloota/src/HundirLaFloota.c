/*
 ============================================================================
 Name        : HundirLaFloota.c
 Author      : Dannycudi
 Version     : 1.0
 Copyright   : Dannycudi
 Description : Juego de hundir la flota.
 ============================================================================
 */

//AIGUA normal es '-'   AIGUA tocada  '*'    TOCAT 'T'    ENFONSAT  'E'

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "boolean.h"

#define MAX 25

struct Cordenades
{
	char fila;
	int columna;
};

typedef struct Cordenades cordenada;

struct Joc
{
	int files;
	int columnes;
	cordenada portavions[4];
	cordenada destructorA[3];
	cordenada destructorB[3];
	cordenada fragataA[2];
	cordenada fragataB[2];
	cordenada submarins[4][1];
	char taulell[MAX][MAX];
};

// Mirar si es posible haciendo una estructura para cada tipo de barco
// y generar una estructura madre que contenga cada una de las diferentes estructuras de barco.
typedef struct Joc joc;

void mostrarConfig(joc dades);
void carregarConfig(joc *dades);
void crearConfig(joc *dades);
void modificarConfig(joc *dades);
void guardarConfig(joc dades);
void eliminarConfig(joc *dades);
void omplirTaulell(joc *dades);
void imprimirTaulell(joc dades);
boolean marcaNoModificats(joc *dades, int op);
void marcarTaulell(joc *dades, char cordenades[4][4], int mida);
void marcarStruct(joc *dades, char cordenades[4][4], int mida, int embarcacio);
boolean comprovaEmbarcacio(joc *dades, char cordenada[4], int mida, int alineacio, int embarcacio);
int digitsNumero(int numero);
int midaFitxer(char *f);
int opcioMenu();
int getAlineacio(char cordenades[4][4], int mida);
char getFila(char cad[10]);
int getColumna(char cad[10]);
boolean posicioValida(char cad[10]);

int main(void) {

//	if (midaFitxer("cfg.txt")) carregarConfig(&dades);
//	else crearConfig(&dades);

//	crearConfig(&dades);
//	imprimirTaulell(dades);
	//mostrarConfig(dades);

//	omplirTaulell(&dades);
//	imprimirTaulell(dades);

	int op;
	joc dades;
	dades.files = -1;
	dades.columnes = -1;

	do {
		op = opcioMenu();

		switch(op) {

		case 1:
			if (midaFitxer("cfg.txt")) {
				carregarConfig(&dades);
				imprimirTaulell(dades);
				printf("\n\n\tFitxer de configuració carregat amb éxit!\n\n");
			}
			else printf("\t\tNo s'ha pogut carregar el fitxer de configuració 'cfg.txt'.");
			break;
		case 2:
			crearConfig(&dades);
			printf("\n\n\tFitxer de configuració creat amb éxit. cfg.txt!\n");
			break;
		case 3:
			if (midaFitxer("cfg.txt") && (dades.columnes != -1 && dades.files != -1)) {
				modificarConfig(&dades);
			}
			else printf("\n\n\t\tNo es troba una configuració a modificar.\n\t\tIntenta llegir o crear-la abans.\n\n");
			break;
		case 4:
			if (midaFitxer("cfg.txt") && (dades.columnes != -1 && dades.files != -1)) {
				eliminarConfig(&dades);
			}
			else printf("\n\n\t\tNo es troba una configuració a eliminar.\n\t\tIntenta llegir o crear-la abans.\n\n");
			break;
		case 5:
			if (midaFitxer("cfg.txt") && (dades.columnes != -1 && dades.files != -1)) {
				mostrarConfig(dades);
			}
			else printf("\n\n\t\tNo es troba una configuració a mostrar.\n\t\tIntenta llegir o crear-la abans.\n\n");
			break;
		}

		printf("\n\n");

	} while(op != 6);

	return 0;

}

void omplirTaulell(joc *dades) {

	int i, j;

	for (i = 0; i < dades->files; i++) {
		for (j = 0; j < dades->columnes; j++) {
			dades->taulell[i][j] = '-';
		}
	}

}

void imprimirTaulell(joc dades) {

	int i, j;
	printf("\n\n\n\t   ");
	for (i = 0; i < dades.columnes; i++) {
		if (i < 10) printf(" %d ", i + 1);
		else printf("%d ", i + 1);
	}
	printf("\n");
	for (i = 0; i < dades.files; i++) {
		printf("\t %c ", i + 'A');
		for (j = 0; j < dades.columnes; j++) {
			printf(" %c ", dades.taulell[i][j]);
		}
		printf("\n");
	}

}

void mostrarConfig(joc dades) {

	int i;

	printf("\tTaulell\n\t\tFiles - %d \t Columnes - %d\n", dades.files, dades.columnes);
	printf("\n\tPortavions\n");
	for (i = 0; i < 4; i++) {
		printf("\t\tFila - %c \t Columna - %d\n", dades.portavions[i].fila, dades.portavions[i].columna);
	}
	printf("\n\tDestructorA\n");
	for (i = 0; i < 3; i++) {
		printf("\t\tFila - %c \t Columna - %d\n", dades.destructorA[i].fila, dades.destructorA[i].columna);
	}
	printf("\n\tDestructorB\n");
	for (i = 0; i < 3; i++) {
		printf("\t\tFila - %c \t Columna - %d\n", dades.destructorB[i].fila, dades.destructorB[i].columna);
	}
	printf("\n\tFragataA\n");
	for (i = 0; i < 2; i++) {
		printf("\t\tFila - %c \t Columna - %d\n", dades.fragataA[i].fila, dades.fragataA[i].columna);
	}
	printf("\n\tFragataB\n");
	for (i = 0; i < 2; i++) {
		printf("\t\tFila - %c \t Columna - %d\n", dades.fragataB[i].fila, dades.fragataB[i].columna);
	}
	printf("\n\tSubmarins\n");
	for (i = 0; i < 4; i++) {
		printf("\t\tFila - %c \t Columna - %d\n", dades.submarins[i][0].fila, dades.submarins[i][0].columna);
	}

	imprimirTaulell(dades);

}

void guardarConfig(joc dades) {

	FILE *cfg;
	int i;

	cfg = fopen("cfg.txt", "w");
	fprintf(cfg, "taulell %dx%d\n", dades.files, dades.columnes);

	fprintf(cfg, "portavions ");
	for (i = 0; i < 4; i++) {
		fprintf(cfg, "%c%d", dades.portavions[i].fila, dades.portavions[i].columna);
		if (i != 3) fprintf(cfg, ",");
	}
	fprintf(cfg, "\n");

	fprintf(cfg, "destructor1 ");
	for (i = 0; i < 3; i++) {
		fprintf(cfg, "%c%d", dades.destructorA[i].fila, dades.destructorA[i].columna);
		if (i != 2) fprintf(cfg, ",");
	}
	fprintf(cfg, "\n");

	fprintf(cfg, "destructor2 ");
	for (i = 0; i < 3; i++) {
		fprintf(cfg, "%c%d", dades.destructorB[i].fila, dades.destructorB[i].columna);
		if (i != 2) fprintf(cfg, ",");
	}
	fprintf(cfg, "\n");

	fprintf(cfg, "fragata1 ");
	for (i = 0; i < 2; i++) {
		fprintf(cfg, "%c%d", dades.fragataA[i].fila, dades.fragataA[i].columna);
		if (i != 1) fprintf(cfg, ",");
	}
	fprintf(cfg, "\n");

	fprintf(cfg, "fragata2 ");
	for (i = 0; i < 2; i++) {
		fprintf(cfg, "%c%d", dades.fragataB[i].fila, dades.fragataB[i].columna);
		if (i != 1) fprintf(cfg, ",");
	}
	fprintf(cfg, "\n");

	fprintf(cfg, "submari ");
	for (i = 0; i < 4; i++) {
		fprintf(cfg, "%c%d", dades.submarins[i][0].fila, dades.submarins[i][0].columna);
		if (i != 3) fprintf(cfg, ",");
	}
	fprintf(cfg, "\n");

	fclose(cfg);

}

void eliminarConfig(joc *dades) {

	char op;

	printf("\n\tLa configuración actual está a punto de eliminarse. ");
	do {
		printf("\n\n\t\t¿Estás seguro? (s/n): ");
		getchar();
		scanf("%c", &op);
	}
	while(op != 's' && op != 'n' && op != 'S' && op != 'N');

	if (op == 's' || op == 'S') {
		remove("cfg.txt");
		printf("\n\t\tFitxer 'cfg.txt' de configuració eliminat amb éxit!\n");
	}

}

void carregarConfig(joc *dades) {

	FILE *cfg;

	cfg = fopen("cfg.txt", "r+");
	char cadena[200], letra, cordenades[4][4];
	int numero, i, cont;

	//Taulell - fread(cadena, sizeof(char), 14, cfg);
	fgets(cadena, 81, cfg);
	dades->files = atoi(&cadena[7]);
	dades->columnes = atoi(&cadena[11]);

	omplirTaulell(dades);

	//Portavions - fread(cadena, sizeof(char), 27, cfg);
	fgets(cadena, 81, cfg);
	cont = 11;
	for (i = 0; i < 4; i++) {
		letra = toupper(cadena[cont]);
		numero = atoi(&cadena[cont+1]);
		dades->portavions[i].fila = letra;
		dades->portavions[i].columna = numero;
		cont = cont + 2 + digitsNumero(numero);
		sprintf(cordenades[i], "%c%d", letra, numero);
	}
	marcarTaulell(dades, cordenades, 4);

	//DestructorA - fread(cadena, sizeof(char), 23, cfg);
	fgets(cadena, 81, cfg);
	cont = 12;
	for (i = 0; i < 3; i++) {
		letra = toupper(cadena[cont]);
		numero = atoi(&cadena[cont+1]);
		dades->destructorA[i].fila = letra;
		dades->destructorA[i].columna = numero;
		cont = cont + 2 + digitsNumero(numero);
		sprintf(cordenades[i], "%c%d", letra, numero);
	}
	marcarTaulell(dades, cordenades, 3);

	//DestructorB - fread(cadena, sizeof(char), 23, cfg);
	fgets(cadena, 81, cfg);
	cont = 12;
	for (i = 0; i < 3; i++) {
		letra = toupper(cadena[cont]);
		numero = atoi(&cadena[cont+1]);
		dades->destructorB[i].fila = letra;
		dades->destructorB[i].columna = numero;
		cont = cont + 2 + digitsNumero(numero);
		sprintf(cordenades[i], "%c%d", letra, numero);
	}
	marcarTaulell(dades, cordenades, 3);

	//FragataA - fread(cadena, sizeof(char), 15, cfg);
	fgets(cadena, 81, cfg);
	cont = 9;
	for (i = 0; i < 2; i++) {
		letra = toupper(cadena[cont]);
		numero = atoi(&cadena[cont+1]);
		dades->fragataA[i].fila = letra;
		dades->fragataA[i].columna = numero;
		cont = cont + 2 + digitsNumero(numero);
		sprintf(cordenades[i], "%c%d", letra, numero);
	}
	marcarTaulell(dades, cordenades, 2);

	//FragataB - fread(cadena, sizeof(char), 15, cfg);
	fgets(cadena, 81, cfg);
	cont = 9;
	for (i = 0; i < 2; i++) {
		letra = toupper(cadena[cont]);
		numero = atoi(&cadena[cont+1]);
		dades->fragataB[i].fila = letra;
		dades->fragataB[i].columna = numero;
		cont = cont + 2 + digitsNumero(numero);
		sprintf(cordenades[i], "%c%d", letra, numero);
	}
	marcarTaulell(dades, cordenades, 2);

	//Submarins - fread(cadena, sizeof(char), 23, cfg);
	fgets(cadena, 81, cfg);
	cont = 8;
	for (i = 0; i < 4; i++) {
		letra = toupper(cadena[cont]);
		numero = atoi(&cadena[cont+1]);
		dades->submarins[i][0].fila = letra;
		dades->submarins[i][0].columna = numero;
		cont = cont + 2 + digitsNumero(numero);
		sprintf(cordenades[0], "%c%d", letra, numero);
		marcarTaulell(dades, cordenades, 1);
	}


	fclose(cfg);

}

void crearConfig(joc *dades) {

	char cordenada[3];
	int alineacio;

	printf("\nCreació del fitxer de configuració");

	printf("\n\nCreació del Taulell\n");
	do {
		printf("Entra el numero de filas: ");
		scanf("%d", &dades->files);
	} while(dades->files < 0 || dades->files > MAX);

	do {
		printf("Entra el numero de columnas: ");
		scanf("%d", &dades->columnes);
	} while(dades->columnes < 0 || dades->columnes > MAX);

	printf("\n\nInicialitzant el taulell...");
	omplirTaulell(dades);

	printf("\n\nCreació de les embarcacions!\n");

	do {

		printf("\nPortavions");
		printf("\nEntra la cordenada icinal: ");
		scanf("%s", cordenada);
		printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal | 3 - Diagonal Inversa)\n\n\tOpció: ");
		scanf("%d", &alineacio);

	} while(!comprovaEmbarcacio(dades, cordenada, 4, alineacio, 0));
	imprimirTaulell(*dades);

	do {

		printf("\nDestructor A");
		printf("\nEntra la cordenada icinal: ");
		scanf("%s", cordenada);
		printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal | 3 - Diagonal Inversa)\n\n\tOpció: ");
		scanf("%d", &alineacio);

	} while(!comprovaEmbarcacio(dades, cordenada, 3, alineacio, 1));
	imprimirTaulell(*dades);

	do {

		printf("\nDestructor B");
		printf("\nEntra la cordenada icinal: ");
		scanf("%s", cordenada);
		printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal | 3 - Diagonal Inversa)\n\n\tOpció: ");
		scanf("%d", &alineacio);

	} while(!comprovaEmbarcacio(dades, cordenada, 3, alineacio, 2));
	imprimirTaulell(*dades);

	do {

		printf("\nFragata A");
		printf("\nEntra la cordenada icinal: ");
		scanf("%s", cordenada);
		printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal | 3 - Diagonal Inversa)\n\n\tOpció: ");
		scanf("%d", &alineacio);

	} while(!comprovaEmbarcacio(dades, cordenada, 2, alineacio, 3));
	imprimirTaulell(*dades);

	do {

		printf("\nFragata B");
		printf("\nEntra la cordenada icinal: ");
		scanf("%s", cordenada);
		printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal | 3 - Diagonal Inversa)\n\n\tOpció: ");
		scanf("%d", &alineacio);

	} while(!comprovaEmbarcacio(dades, cordenada, 2, alineacio, 4));
	imprimirTaulell(*dades);

	do {

		printf("\nSubmari A");
		printf("\nEntra la cordenada: ");
		scanf("%s", cordenada);

	} while(!comprovaEmbarcacio(dades, cordenada, 1, 0, 5));
	imprimirTaulell(*dades);

	do {

		printf("\nSubmari B");
		printf("\nEntra la cordenada: ");
		scanf("%s", cordenada);

	} while(!comprovaEmbarcacio(dades, cordenada, 1, 0, 6));
	imprimirTaulell(*dades);

	do {

		printf("\nSubmari C");
		printf("\nEntra la cordenada: ");
		scanf("%s", cordenada);

	} while(!comprovaEmbarcacio(dades, cordenada, 1, 0, 7));
	imprimirTaulell(*dades);

	do {

		printf("\nSubmari D");
		printf("\nEntra la cordenada: ");
		scanf("%s", cordenada);

	} while(!comprovaEmbarcacio(dades, cordenada, 1, 0, 8));
	imprimirTaulell(*dades);


	guardarConfig(*dades);

}

void modificarConfig(joc *dades) {

	int op, aux, auxAnterior;
	char cordenada[4];

	printf("\n\n\n");

	do {
		printf("MODIFICAR CONFIGURACIÓ\n\n\tQuè vols modificar?\n");
		printf("\n\t\t1) Files del taulell\n\t\t2) Columnes del taulell\n\t\t3) Portavions\n\t\t4) DestructorA\n\t\t5) DestructorB\n\t\t6) FragataA\n\t\t7) FragataB");
		printf("\n\t\t8) Submari A\n\t\t9) Submari B\n\t\t10) Submari C\n\t\t11) Submari D");
		printf("\n\n\t\t\tOpció: ");
		scanf("%d", &op);
	} while(op < 1 || op > 11);


	switch (op) {
		case 1:

			printf("\n\n\tEntra les files del taulell: ");
			scanf("%d", &aux);

			auxAnterior = dades->files;

			dades->files = aux;

			if (marcaNoModificats(dades, op) == TRUE) printf("\n\t\tFiles modificades amb éxit!\n");
			else {
				dades->files = auxAnterior;
				printf("\n\t\tError al fer la modificació!\n");
			}

			break;
		case 2:

			printf("\n\n\tEntra les columnes del taulell: ");
			scanf("%d", &aux);

			auxAnterior = dades->columnes;
			dades->columnes = aux;

			if (marcaNoModificats(dades, op) == TRUE) printf("\n\t\tColumnes modificades amb éxit!\n");
			else {
				dades->columnes = auxAnterior;
				printf("\n\t\tError al fer la modificació!\n");
			}

			break;
		case 3:

			printf("\nPortavions");
			printf("\nEntra la cordenada icinal: ");
			scanf("%s", cordenada);
			printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal | 3 - Diagonal Inversa)\n\n\tOpció: ");
			scanf("%d", &aux);

			if (marcaNoModificats(dades, op) == TRUE) {
				if (comprovaEmbarcacio(dades, cordenada, 4, aux, 0)) printf("\n\t\tPortavions modificat amb éxit!\n");
				else printf("\n\t\tError al fer la modificació!\n");
			}

			break;
		case 4:

			printf("\nDestructorA");
			printf("\nEntra la cordenada icinal: ");
			scanf("%s", cordenada);
			printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal | 3 - Diagonal Inversa)\n\n\tOpció: ");
			scanf("%d", &aux);

			if (marcaNoModificats(dades, op) == TRUE) {
				if (comprovaEmbarcacio(dades, cordenada, 3, aux, 1)) printf("\n\t\tDestructorA modificat amb éxit!\n");
				else printf("\n\t\tError al fer la modificació!\n");
			}

			break;
		case 5:

			printf("\nDestructorB");
			printf("\nEntra la cordenada icinal: ");
			scanf("%s", cordenada);
			printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal | 3 - Diagonal Inversa)\n\n\tOpció: ");
			scanf("%d", &aux);

			if (marcaNoModificats(dades, op) == TRUE) {
				if (comprovaEmbarcacio(dades, cordenada, 3, aux, 2)) printf("\n\t\tDestructorB modificat amb éxit!\n");
				else printf("\n\t\tError al fer la modificació!\n");
			}

			break;
		case 6:

			printf("\nFragataA");
			printf("\nEntra la cordenada icinal: ");
			scanf("%s", cordenada);
			printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal | 3 - Diagonal Inversa)\n\n\tOpció: ");
			scanf("%d", &aux);

			if (marcaNoModificats(dades, op) == TRUE) {
				if (comprovaEmbarcacio(dades, cordenada, 2, aux, 3)) printf("\n\t\tFragataA modificat amb éxit!\n");
				else printf("\n\t\tError al fer la modificació!\n");
			}

			break;
		case 7:

			printf("\nFragataB");
			printf("\nEntra la cordenada icinal: ");
			scanf("%s", cordenada);
			printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal | 3 - Diagonal Inversa)\n\n\tOpció: ");
			scanf("%d", &aux);

			if (marcaNoModificats(dades, op) == TRUE) {
				if (comprovaEmbarcacio(dades, cordenada, 2, aux, 4)) printf("\n\t\tFragataB modificat amb éxit!\n");
				else printf("\n\t\tError al fer la modificació!\n");
			}

			break;
		case 8:

			printf("\nSubmariA");
			printf("\nEntra la cordenada: ");
			scanf("%s", cordenada);

			if (marcaNoModificats(dades, op) == TRUE) {
				if (comprovaEmbarcacio(dades, cordenada, 1, aux, 5)) printf("\n\t\tSubmariA modificat amb éxit!\n");
				else printf("\n\t\tError al fer la modificació!\n");
			}

			break;
		case 9:

			printf("\nSubmariB");
			printf("\nEntra la cordenada: ");
			scanf("%s", cordenada);

			if (marcaNoModificats(dades, op) == TRUE) {
				if (comprovaEmbarcacio(dades, cordenada, 1, aux, 6)) printf("\n\t\tSubmariB modificat amb éxit!\n");
				else printf("\n\t\tError al fer la modificació!\n");
			}

			break;
		case 10:

			printf("\nSubmariC");
			printf("\nEntra la cordenada: ");
			scanf("%s", cordenada);

			if (marcaNoModificats(dades, op) == TRUE) {
				if (comprovaEmbarcacio(dades, cordenada, 1, aux, 7)) printf("\n\t\tSubmariC modificat amb éxit!\n");
				else printf("\n\t\tError al fer la modificació!\n");
			}

			break;
		case 11:

			printf("\nSubmariD");
			printf("\nEntra la cordenada: ");
			scanf("%s", cordenada);

			if (marcaNoModificats(dades, op) == TRUE) {
				if (comprovaEmbarcacio(dades, cordenada, 1, aux, 8)) printf("\n\t\tSubmariD	 modificat amb éxit!\n");
				else printf("\n\t\tError al fer la modificació!\n");
			}

			break;
	}

	guardarConfig(*dades);

}

boolean marcaNoModificats(joc *dades, int op) {

	int i;
	char cordenades[4][4];
	boolean correcte = TRUE;

	omplirTaulell(dades);


	if (op != 3 && correcte) {
		for (i = 0; i < 4; i++) snprintf(cordenades[i], sizeof(cordenades[i]), "%c%d", dades->portavions[i].fila, dades->portavions[i].columna);
		correcte = comprovaEmbarcacio(dades, cordenades[0], 4, getAlineacio(cordenades, 4), 0);
	}
	if (op != 4 && correcte) {
		for (i = 0; i < 3; i++) sprintf(cordenades[i], "%c%d", dades->destructorA[i].fila, dades->destructorA[i].columna);
		correcte = comprovaEmbarcacio(dades, cordenades[0], 3, getAlineacio(cordenades, 3), 1);
	}
	if (op != 5 && correcte) {
		for (i = 0; i < 3; i++) sprintf(cordenades[i], "%c%d", dades->destructorB[i].fila, dades->destructorB[i].columna);
		correcte = comprovaEmbarcacio(dades, cordenades[0], 3, getAlineacio(cordenades, 3), 2);
	}
	if (op != 6 && correcte) {
		for (i = 0; i < 2; i++) sprintf(cordenades[i], "%c%d", dades->fragataA[i].fila, dades->fragataA[i].columna);
		correcte = comprovaEmbarcacio(dades, cordenades[0], 2, getAlineacio(cordenades, 2), 3);
	}
	if (op != 7 && correcte) {
		for (i = 0; i < 2; i++) sprintf(cordenades[i], "%c%d", dades->fragataB[i].fila, dades->fragataB[i].columna);
		correcte = comprovaEmbarcacio(dades, cordenades[0], 2, getAlineacio(cordenades, 2), 4);
	}
	if (op != 8 && correcte) {
		sprintf(cordenades[0], "%c%d", dades->submarins[0][0].fila, dades->submarins[0][0].columna);
		correcte = comprovaEmbarcacio(dades, cordenades[0], 1, getAlineacio(cordenades, 1), 5);
	}
	if (op != 9 && correcte) {
		sprintf(cordenades[0], "%c%d", dades->submarins[1][0].fila, dades->submarins[1][0].columna);
		correcte = comprovaEmbarcacio(dades, cordenades[0], 1, getAlineacio(cordenades, 1), 6);
	}
	if (op != 10 && correcte) {
		sprintf(cordenades[0], "%c%d", dades->submarins[2][0].fila, dades->submarins[2][0].columna);
		correcte = comprovaEmbarcacio(dades, cordenades[0], 1, getAlineacio(cordenades, 1), 7);
	}
	if (op != 11 && correcte) {
		sprintf(cordenades[0], "%c%d", dades->submarins[3][0].fila, dades->submarins[3][0].columna);
		correcte = comprovaEmbarcacio(dades, cordenades[0], 1, getAlineacio(cordenades, 1), 8);
	}

	return correcte;

}


boolean comprovaEmbarcacio(joc *dades, char cordenada[4], int mida, int alineacio, int embarcacio) {

	int i;
	char cordenades[mida][4];
	boolean correcte = TRUE;

	//Alineació | -1 - Error | 0 - Horizontal | 1 - Vertical | 2 - Diagonal A | 3 - Diagonal B

	strncpy(cordenades[0], cordenada, 4);
	cordenades[0][4]='\0';
	for (i = 1; i < mida; i++) {

		switch (alineacio) {
			case 0:
				snprintf(cordenades[i], sizeof(cordenades[i]), "%c%d", getFila(cordenada), (getColumna(cordenada) + i));
				cordenades[i][4]='\0';
			break;
			case 1:
				snprintf(cordenades[i], sizeof(cordenades[i]), "%c%d", (getFila(cordenada) + i), getColumna(cordenada));
				cordenades[i][4]='\0';
			break;
			case 2:
				snprintf(cordenades[i], sizeof(cordenades[i]), "%c%d", (getFila(cordenada) + i), (getColumna(cordenada) + i));
				cordenades[i][4]='\0';
			break;
			case 3:
				snprintf(cordenades[i], sizeof(cordenades[i]), "%c%d", (getFila(cordenada) + i), (getColumna(cordenada) - i));
				cordenades[i][4]='\0';
			break;
		}

	}

	for (i = 0; i < mida; i++) {

		if (!posicioValida(cordenades[i])) correcte = FALSE;
		if (getFila(cordenades[i]) > 'A' + dades->files) correcte = FALSE;
		if (getColumna(cordenades[i])  > dades->columnes) correcte = FALSE;
		if (dades->taulell[getFila(cordenades[i]) - 'A'][getColumna(cordenades[i])] != '-') correcte = FALSE;

	}

	if (correcte) {
		marcarTaulell(dades, cordenades, mida);
		marcarStruct(dades, cordenades, mida, embarcacio);
	}

	return correcte;

}


void marcarTaulell(joc *dades, char cordenades[4][4], int mida) {

	int i;
	char lletra;

	switch(mida) {
	case 1:
		lletra = 'S';
		break;
	case 2:
		lletra = 'F';
		break;
	case 3:
		lletra = 'D';
		break;
	case 4:
		lletra = 'P';
		break;
	}


	for (i = 0; i < mida; i++) {

		dades->taulell[getFila(cordenades[i])-'A'][getColumna(cordenades[i]) - 1] = lletra;

	}

}

void marcarStruct(joc *dades, char cordenades[4][4], int mida, int embarcacio) {

	int i = 0;
	for (i = 0; i < mida; i++) {

		switch(embarcacio) {
			case 0:
				dades->portavions[i].fila = getFila(cordenades[i]);
				dades->portavions[i].columna = getColumna(cordenades[i]);
			break;
			case 1:
				dades->destructorA[i].fila = getFila(cordenades[i]);
				dades->destructorA[i].columna = getColumna(cordenades[i]);
			break;
			case 2:
				dades->destructorB[i].fila = getFila(cordenades[i]);
				dades->destructorB[i].columna = getColumna(cordenades[i]);
			break;
			case 3:
				dades->fragataA[i].fila = getFila(cordenades[i]);
				dades->fragataA[i].columna = getColumna(cordenades[i]);
			break;
			case 4:
				dades->fragataB[i].fila = getFila(cordenades[i]);
				dades->fragataB[i].columna = getColumna(cordenades[i]);
			break;
			case 5:
				dades->submarins[0][i].fila = getFila(cordenades[i]);
				dades->submarins[0][i].columna = getColumna(cordenades[i]);
			break;
			case 6:
				dades->submarins[1][i].fila = getFila(cordenades[i]);
				dades->submarins[1][i].columna = getColumna(cordenades[i]);
			break;
			case 7:
				dades->submarins[2][i].fila = getFila(cordenades[i]);
				dades->submarins[2][i].columna = getColumna(cordenades[i]);
			break;
			case 8:
				dades->submarins[3][i].fila = getFila(cordenades[i]);
				dades->submarins[3][i].columna = getColumna(cordenades[i]);
			break;
		}

	}

}

boolean posicioValida(char cad[10]) {

	boolean valid = TRUE;
	int i;
	for (i = 1; i < strlen(cad); i++) {
		if (!isdigit(cad[i])) valid = FALSE;
	}

	if (isalpha(cad[0]) && valid) return TRUE;
	return FALSE;

}

int getAlineacio(char cordenades[4][4], int mida) {

	int al = -1;

	if (getFila(cordenades[0]) == getFila(cordenades[1]) && getColumna(cordenades[1]) == (getColumna(cordenades[0]) + 1)) al = 0;
	else if (getFila(cordenades[1]) == (getFila(cordenades[0]) + 1) && getColumna(cordenades[0]) == getColumna(cordenades[1])) al = 1;
	else if (getFila(cordenades[1]) == (getFila(cordenades[0]) + 1) && getColumna(cordenades[1]) == (getColumna(cordenades[0]) + 1)) al = 2;
	else if (getFila(cordenades[1]) == (getFila(cordenades[0]) + 1) && getColumna(cordenades[1]) == (getColumna(cordenades[0]) - 1)) al = 3;
	else if (mida == 1) al = 0;

	return al;
}

char getFila(char cad[10]) {

	return toupper(cad[0]);

}

int getColumna(char cad[10]) {

	char cadena[10] = "";
	int i;

	for (i = 0; i < strlen(cad); i++) {
		cadena[i] = cad[i+1];
	}

	cadena[i] = '\0';

	return atoi(cadena);

}

int digitsNumero(int numero) {

	int cont = 0;

	while (numero>0) {
		numero = numero / 10;
		cont++;
	}

	return cont;
}

int midaFitxer(char *f) {

	int mida = 0;
	FILE *cfg;
	cfg = fopen(f, "a+");
	fseek(cfg, 0L, SEEK_END);
	mida=ftell(cfg);
	fclose(cfg);

	return mida;
}

int opcioMenu() {

	int op;

	do {
		printf("\n\nMENÚ PRINCIPAL\n\n");
		printf("\t1) Llegir configuració\n\t2) Crear configuració\n\t3) Modificar configuració\n\t4) Eliminar configuració\n\t5) Mostra Configuració\n\t6) Srotir");
		printf("\n\n\t\tOpció: ");
		scanf("%d", &op);
	}
	while (op < 1 || op > 6);

	return op;
}

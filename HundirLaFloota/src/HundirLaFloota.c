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
void omplirTaulell(joc *dades);
void imprimirTaulell(joc dades);
boolean comprovaEmbarcacio(joc dades, char cordenades[4][4], int mida, int alineacio);
int digitsNumero(int numero);
int midaFitxer(char *f);
int opcioMeu();
char getFila(char cad[10]);
int getColumna(char cad[10]);
boolean posicioValida(char cad[10]);

int main(void) {

	joc dades;

//	if (midaFitxer("cfg.txt")) carregarConfig(&dades);
//	else crearConfig(&dades);

	crearConfig(&dades);

	//mostrarConfig(dades);

//	omplirTaulell(&dades);
//	imprimirTaulell(dades);

	int op;

	do {
		op = 1;
		//op = opcioMenu();

	} while(op < 1 || op > 6);

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
	printf("\n\n\n");
	for (i = 0; i < dades.files; i++) {
		printf("\t");
		for (j = 0; j < dades.columnes; j++) {
			printf("%c ", dades.taulell[i][j]);
		}
		printf("\n");
	}

}

void mostrarConfig(joc dades) {

	int i;

	printf("Taulell\n%d - %d\n", dades.files, dades.columnes);
	printf("\nPortavions\n");
	for (i = 0; i < 4; i++) {
		printf("Fila - %c \t Columna - %d\n", dades.portavions[i].fila, dades.portavions[i].columna);
	}
	printf("\nDestructorA\n");
	for (i = 0; i < 3; i++) {
		printf("Fila - %c \t Columna - %d\n", dades.destructorA[i].fila, dades.destructorA[i].columna);
	}
	printf("\nDestructorB\n");
	for (i = 0; i < 3; i++) {
		printf("Fila - %c \t Columna - %d\n", dades.destructorB[i].fila, dades.destructorB[i].columna);
	}
	printf("\nFragataA\n");
	for (i = 0; i < 2; i++) {
		printf("Fila - %c \t Columna - %d\n", dades.fragataA[i].fila, dades.fragataA[i].columna);
	}
	printf("\nFragataB\n");
	for (i = 0; i < 2; i++) {
		printf("Fila - %c \t Columna - %d\n", dades.fragataB[i].fila, dades.fragataB[i].columna);
	}
	printf("\nSubmarins\n");
	for (i = 0; i < 4; i++) {
		printf("Fila - %c \t Columna - %d\n", dades.submarins[i][0].fila, dades.submarins[i][0].columna);
	}

}

void carregarConfig(joc *dades) {

	FILE *cfg;

	cfg = fopen("cfg.txt", "r+");
	char cadena[200], letra;
	int numero, i, cont;

	//Taulell - fread(cadena, sizeof(char), 14, cfg);
	fgets(cadena, 81, cfg);
	dades->columnes = atoi(&cadena[11]);
	dades->files = atoi(&cadena[7]);

	//Portavions - fread(cadena, sizeof(char), 27, cfg);
	fgets(cadena, 81, cfg);
	cont = 11;
	for (i = 0; i < 4; i++) {
		letra = cadena[cont];
		numero = atoi(&cadena[cont+1]);
		dades->portavions[i].fila = letra;
		dades->portavions[i].columna = numero;
		cont = cont + 2 + digitsNumero(numero);
	}

	//DestructorA - fread(cadena, sizeof(char), 23, cfg);
	fgets(cadena, 81, cfg);
	cont = 12;
	for (i = 0; i < 3; i++) {
		letra = cadena[cont];
		numero = atoi(&cadena[cont+1]);
		dades->destructorA[i].fila = letra;
		dades->destructorA[i].columna = numero;
		cont = cont + 2 + digitsNumero(numero);
	}

	//DestructorB - fread(cadena, sizeof(char), 23, cfg);
	fgets(cadena, 81, cfg);
	cont = 12;
	for (i = 0; i < 3; i++) {
		letra = cadena[cont];
		numero = atoi(&cadena[cont+1]);
		dades->destructorB[i].fila = letra;
		dades->destructorB[i].columna = numero;
		cont = cont + 2 + digitsNumero(numero);
	}

	//FragataA - fread(cadena, sizeof(char), 15, cfg);
	fgets(cadena, 81, cfg);
	cont = 9;
	for (i = 0; i < 2; i++) {
		letra = cadena[cont];
		numero = atoi(&cadena[cont+1]);
		dades->fragataA[i].fila = letra;
		dades->fragataA[i].columna = numero;
		cont = cont + 2 + digitsNumero(numero);
	}

	//FragataB - fread(cadena, sizeof(char), 15, cfg);
	fgets(cadena, 81, cfg);
	cont = 9;
	for (i = 0; i < 2; i++) {
		letra = cadena[cont];
		numero = atoi(&cadena[cont+1]);
		dades->fragataB[i].fila = letra;
		dades->fragataB[i].columna = numero;
		cont = cont + 2 + digitsNumero(numero);
	}

	//Submarins - fread(cadena, sizeof(char), 23, cfg);
	fgets(cadena, 81, cfg);
	cont = 8;
	for (i = 0; i < 4; i++) {
		letra = cadena[cont];
		numero = atoi(&cadena[cont+1]);
		dades->submarins[i][0].fila = letra;
		dades->submarins[i][0].columna = numero;
		cont = cont + 2 + digitsNumero(numero);
	}

	fclose(cfg);

}

void crearConfig(joc *dades) {

	char cordenades[4][4];
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

	printf("\n\nCreació de les embarcacions!\n");

	do {

		printf("\nPortavions");
		printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal)");
		scanf("%d", &alineacio);
		printf("\nEntra les 4 cordenades separades per un espai: ");
		scanf("%s %s %s %s", cordenades[0], cordenades[1], cordenades[2], cordenades[3]);

	} while(!comprovaEmbarcacio(*dades, cordenades, 4, alineacio));

	printf("%c %d\n", getFila(cordenades[0]), getColumna(cordenades[0]));


}

boolean comprovaEmbarcacio(joc dades, char cordenades[4][4], int mida, int alineacio) {

	int i, c;
	char f;
	boolean correcte = TRUE;

	//Alineació | -1 - Error | 0 - Horizontal | 1 - Vertical | 2 - Diagonal

	f = getFila(cordenades[0]);
	c = getColumna(cordenades[0]);
	for (i = 1; i < mida; i++) {

		switch (alineacio) {
			case 0:
				if ((getFila(cordenades[i]) != f || getColumna(cordenades[i]) != c + i) && (getFila(cordenades[i]) != f || getColumna(cordenades[i]) != c - i)) correcte = FALSE;
			break;
			case 1:
				if ((getFila(cordenades[i]) != f + i || getColumna(cordenades[i]) != c) && (getFila(cordenades[i]) != f - i || getColumna(cordenades[i]) != c)) correcte = FALSE;
			break;
			case 2:
				correcte = FALSE;
			break;
		}

	}

	for (i = 0; i < mida; i++) {

		if (!posicioValida(cordenades[i])) correcte = FALSE;
		if (getFila(cordenades[i]) > 'A' + dades.files) correcte = FALSE;
		else if (getColumna(cordenades[i]) > dades.columnes) correcte = FALSE;

	}

	return correcte;

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

char getFila(char cad[10]) {

	return cad[0];

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

	int mida;
	FILE *cfg;
	cfg = fopen(f, "a+");
	fseek(cfg, 0L, SEEK_END);
	mida=ftell(cfg);
	fclose(cfg);

	return mida;
}

int opcioMeu() {

	return 0;
}

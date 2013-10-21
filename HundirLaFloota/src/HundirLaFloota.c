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
void guardarConfig(joc dades);
void omplirTaulell(joc *dades);
void imprimirTaulell(joc dades);
void marcarTaulell(joc *dades, char cordenades[4][4], int mida);
boolean comprovaEmbarcacio(joc *dades, char cordenada[4], int mida, int alineacio);
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
	imprimirTaulell(dades);
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

	fclose(cfg);

}

void carregarConfig(joc *dades) {

	FILE *cfg;

	cfg = fopen("cfg.txt", "r+");
	char cadena[200], letra;
	int numero, i, cont;

	//Taulell - fread(cadena, sizeof(char), 14, cfg);
	fgets(cadena, 81, cfg);
	dades->files = atoi(&cadena[7]);
	dades->columnes = atoi(&cadena[11]);

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
		printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal Esquerra-Dreta | 3 - Diagonal Dreta-Esquerra)");
		scanf("%d", &alineacio);
		printf("\nEntra la cordenada icinal: ");
		scanf("%s", cordenada);

	} while(!comprovaEmbarcacio(dades, cordenada, 4, alineacio));

	do {

		printf("\nDestructor A");
		printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal Esquerra-Dreta | 3 - Diagonal Dreta-Esquerra)");
		scanf("%d", &alineacio);
		printf("\nEntra la cordenada icinal: ");
		scanf("%s", cordenada);

	} while(!comprovaEmbarcacio(dades, cordenada, 3, alineacio));

	do {

		printf("\nDestructor B");
		printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal Esquerra-Dreta | 3 - Diagonal Dreta-Esquerra)");
		scanf("%d", &alineacio);
		printf("\nEntra la cordenada icinal: ");
		scanf("%s", cordenada);

	} while(!comprovaEmbarcacio(dades, cordenada, 3, alineacio));

	do {

		printf("\nFragata A");
		printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal Esquerra-Dreta | 3 - Diagonal Dreta-Esquerra)");
		scanf("%d", &alineacio);
		printf("\nEntra la cordenada icinal: ");
		scanf("%s", cordenada);

	} while(!comprovaEmbarcacio(dades, cordenada, 2, alineacio));

	do {

		printf("\nFragata B");
		printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal Esquerra-Dreta | 3 - Diagonal Dreta-Esquerra)");
		scanf("%d", &alineacio);
		printf("\nEntra la cordenada icinal: ");
		scanf("%s", cordenada);

	} while(!comprovaEmbarcacio(dades, cordenada, 2, alineacio));

	do {

		printf("\nSubmari A");
		printf("\nEntra la cordenada icinal: ");
		scanf("%s", cordenada);

	} while(!comprovaEmbarcacio(dades, cordenada, 1, 0));

	do {

		printf("\nSubmari B");
		printf("\nEntra la cordenada icinal: ");
		scanf("%s", cordenada);

	} while(!comprovaEmbarcacio(dades, cordenada, 1, 0));

	do {

		printf("\nSubmari C");
		printf("\nEntra la cordenada icinal: ");
		scanf("%s", cordenada);

	} while(!comprovaEmbarcacio(dades, cordenada, 1, 0));

	do {

		printf("\nSubmari D");
		printf("\nEntra la cordenada icinal: ");
		scanf("%s", cordenada);

	} while(!comprovaEmbarcacio(dades, cordenada, 1, 0));


}

boolean comprovaEmbarcacio(joc *dades, char cordenada[4], int mida, int alineacio) {

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

		printf("\n\n %s", cordenades[i]);
		if (!posicioValida(cordenades[i])) correcte = FALSE;
		printf("\nPosició Valida -> %d", correcte);
		if (getFila(cordenades[i]) > 'A' + dades->files) correcte = FALSE;
		printf("\nFila -> %d", correcte);
		if (getColumna(cordenades[i])  > dades->columnes) correcte = FALSE;
		printf("\nColumna -> %d", correcte);
		if (dades->taulell[getFila(cordenades[i]) - 'A'][getColumna(cordenades[i])] != '-') correcte = FALSE;
		printf("\nTaulell -> %d", correcte);

	}

	if (correcte) {
		marcarTaulell(dades, cordenades, mida);
		imprimirTaulell(*dades);
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

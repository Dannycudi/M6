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
void marcarStruct(joc *dades, char cordenades[4][4], int mida, int embarcacio);
boolean comprovaEmbarcacio(joc *dades, char cordenada[4], int mida, int alineacio, int embarcacio);
int digitsNumero(int numero);
int midaFitxer(char *f);
int opcioMenu();
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

	do {
		op = opcioMenu();
		printf("\n\n");

		switch(op) {

		case 1:
			if (midaFitxer("cfg.txt")) {
				carregarConfig(&dades);
				printf("\t\tFitxer de configuració carregat amb éxit!\n\n");
				imprimirTaulell(dades);
			}
			else printf("\t\tNo s'ha pogut carregar el fitxer de configuració 'cfg.txt'.");
			break;
		case 2:
			crearConfig(&dades);
			printf("\t\tFitxer de configuració creat amb éxit. cfg.txt!");
			break;
		case 5:
			mostrarConfig(dades);
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
	for (i = 0; i < 2; i++) {
		fprintf(cfg, "%c%d", dades.submarins[i][0].fila, dades.submarins[i][0].columna);
		if (i != 1) fprintf(cfg, ",");
	}
	fprintf(cfg, "\n");

	fclose(cfg);

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

	do {

		printf("\nDestructor A");
		printf("\nEntra la cordenada icinal: ");
		scanf("%s", cordenada);
		printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal | 3 - Diagonal Inversa)\n\n\tOpció: ");
		scanf("%d", &alineacio);

	} while(!comprovaEmbarcacio(dades, cordenada, 3, alineacio, 1));

	do {

		printf("\nDestructor B");
		printf("\nEntra la cordenada icinal: ");
		scanf("%s", cordenada);
		printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal | 3 - Diagonal Inversa)\n\n\tOpció: ");
		scanf("%d", &alineacio);

	} while(!comprovaEmbarcacio(dades, cordenada, 3, alineacio, 2));

	do {

		printf("\nFragata A");
		printf("\nEntra la cordenada icinal: ");
		scanf("%s", cordenada);
		printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal | 3 - Diagonal Inversa)\n\n\tOpció: ");
		scanf("%d", &alineacio);

	} while(!comprovaEmbarcacio(dades, cordenada, 2, alineacio, 3));

	do {

		printf("\nFragata B");
		printf("\nEntra la cordenada icinal: ");
		scanf("%s", cordenada);
		printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal | 3 - Diagonal Inversa)\n\n\tOpció: ");
		scanf("%d", &alineacio);

	} while(!comprovaEmbarcacio(dades, cordenada, 2, alineacio, 4));

	do {

		printf("\nSubmari A");
		printf("\nEntra la cordenada: ");
		scanf("%s", cordenada);

	} while(!comprovaEmbarcacio(dades, cordenada, 1, 0, 5));

	do {

		printf("\nSubmari B");
		printf("\nEntra la cordenada: ");
		scanf("%s", cordenada);

	} while(!comprovaEmbarcacio(dades, cordenada, 1, 0, 6));

	do {

		printf("\nSubmari C");
		printf("\nEntra la cordenada: ");
		scanf("%s", cordenada);

	} while(!comprovaEmbarcacio(dades, cordenada, 1, 0, 7));

	do {

		printf("\nSubmari D");
		printf("\nEntra la cordenada: ");
		scanf("%s", cordenada);

	} while(!comprovaEmbarcacio(dades, cordenada, 1, 0, 8));


	guardarConfig(*dades);

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

		//printf("\n\n%s", cordenades[i]);
		if (!posicioValida(cordenades[i])) correcte = FALSE;
		//printf("\nPosició Valida -> %d", correcte);
		if (getFila(cordenades[i]) > 'A' + dades->files) correcte = FALSE;
		//printf("\nFila -> %d", correcte);
		if (getColumna(cordenades[i])  > dades->columnes) correcte = FALSE;
		//printf("\nColumna -> %d", correcte);
		if (dades->taulell[getFila(cordenades[i]) - 'A'][getColumna(cordenades[i])] != '-') correcte = FALSE;
		//printf("\nTaulell -> %d", correcte);

	}

	if (correcte) {
		marcarTaulell(dades, cordenades, mida);
		marcarStruct(dades, cordenades, mida, embarcacio);
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

	int mida;
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

/*
 ============================================================================
 Name        : HundirLaFlota-Binario.c
 Author      : Dannycudi
 Version     : 1.0
 Copyright   : Dannycudi
 Description : Juego Hundir La Flota guardando en Binario
 	 	 	   AIGUA '-'   AIGUA tocada  '*'    TOCAT 'T'    ENFONSAT  'E'
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "boolean.h"

#define MAX 30

typedef struct posicion
{
	int fila;
	int columna;
} posicion;

typedef struct barco
{
	char tipo;
	posicion casillas[4];
} barco;

typedef struct tablero
{
	int filas;
	int columnas;
} tablero;

typedef struct juego
{
	tablero tablero;
	barco flota[9];
} juego;

//Teclado SI * NO -

void mostrarConfig(juego datos);
void carregarConfig(juego *datos);
void crearConfig(juego *datos);
void modificarConfig(juego *datos);
void guardarConfig(juego datos);
void eliminarConfig(juego *datos);
void omplirTaulell(juego *datos);
void imprimirTaulell(juego datos);
boolean marcaNoModificats(juego *datos, int op);
void marcarTaulell(juego *datos, char cordenades[4][4], int mida);
void marcarStruct(juego *datos, char cordenades[4][4], int mida, int embarcacio);
boolean comprovaEmbarcacio(juego *datos, char cordenada[4], int mida, int alineacio, int embarcacio);
int digitsNumero(int numero);
int midaFitxer(char *f);
int opcioMenu();
int getAlineacio(char cordenades[4][4], int mida);
char getFila(char cad[10]);
int getColumna(char cad[10]);
boolean posicioValida(char cad[10]);
int primerEspai(char cad[100]);
int getMidaBarco(char lletra);

char casillas[MAX][MAX];

int main(void) {

	int op;
	juego datos;


	return 0;

}


void omplirTaulell(juego *datos) {

	int i, j;

	for (i = 0; i < datos->tablero.filas; i++) {
		for (j = 0; j < datos->tablero.columnas; j++) {
			casillas[i][j] = '-';
		}
	}

}

void imprimirTaulell(juego datos) {

	int i, j;
	printf("\n\n\n\t   ");
	for (i = 0; i < datos.tablero.columnas; i++) {
		if (i < 10) printf(" %d ", i + 1);
		else printf("%d ", i + 1);
	}
	printf("\n");
	for (i = 0; i < datos.tablero.filas; i++) {
		printf("\t %c ", i + 'A');
		for (j = 0; j < datos.tablero.columnas; j++) {
			printf(" %c ", casillas[i][j]);
		}
		printf("\n");
	}

}

void mostrarConfig(juego datos) {

	int i;

	printf("\tTaulell\n\t\tFiles - %d \t Columnes - %d\n", datos.tablero.filas, datos.tablero.columnas);

	printf("\n\tPortavions\n");
	for (i = 0; i < 4; i++) {
		printf("\t\tFila - %c \t Columna - %d\n", datos.flota[0].casillas[i].fila, datos.flota[0].casillas[i].columna);
	}
	printf("\n\tDestructorA\n");
	for (i = 0; i < 3; i++) {
		printf("\t\tFila - %c \t Columna - %d\n", datos.flota[1].casillas[i].fila, datos.flota[1].casillas[i].columna);
	}
	printf("\n\tDestructorB\n");
	for (i = 0; i < 3; i++) {
		printf("\t\tFila - %c \t Columna - %d\n", datos.flota[2].casillas[i].fila, datos.flota[2].casillas[i].columna);
	}
	printf("\n\tFragataA\n");
	for (i = 0; i < 2; i++) {
		printf("\t\tFila - %c \t Columna - %d\n", datos.flota[3].casillas[i].fila, datos.flota[3].casillas[i].columna);
	}
	printf("\n\tFragataB\n");
	for (i = 0; i < 2; i++) {
		printf("\t\tFila - %c \t Columna - %d\n", datos.flota[4].casillas[i].fila, datos.flota[4].casillas[i].columna);
	}
	printf("\n\tSubmarins\n");
	for (i = 0; i < 4; i++) {
		printf("\t\tFila - %c \t Columna - %d\n", datos.flota[5+i].casillas[0].fila, datos.flota[5+i].casillas[0].columna);
	}

	imprimirTaulell(datos);

}

void guardarConfig(juego datos) {

	FILE *cfg;
	int i;

	cfg = fopen("cfg.txt", "w");
	fprintf(cfg, "taulell %dx%d\n", datos.tablero.filas, datos.tablero.columnas);

	fprintf(cfg, "portavions ");
	for (i = 0; i < 4; i++) {
		fprintf(cfg, "%c%d", datos.flota[0].casillas[i].fila, datos.flota[0].casillas[i].columna);
		if (i != 3) fprintf(cfg, ",");
	}
	fprintf(cfg, "\n");

	fprintf(cfg, "destructor1 ");
	for (i = 0; i < 3; i++) {
		fprintf(cfg, "%c%d", datos.flota[1].casillas[i].fila, datos.flota[1].casillas[i].columna);
		if (i != 2) fprintf(cfg, ",");
	}
	fprintf(cfg, "\n");

	fprintf(cfg, "destructor2 ");
	for (i = 0; i < 3; i++) {
		fprintf(cfg, "%c%d", datos.flota[2].casillas[i].fila, datos.flota[2].casillas[i].columna);
		if (i != 2) fprintf(cfg, ",");
	}
	fprintf(cfg, "\n");

	fprintf(cfg, "fragata1 ");
	for (i = 0; i < 2; i++) {
		fprintf(cfg, "%c%d", datos.flota[3].casillas[i].fila, datos.flota[3].casillas[i].columna);
		if (i != 1) fprintf(cfg, ",");
	}
	fprintf(cfg, "\n");

	fprintf(cfg, "fragata2 ");
	for (i = 0; i < 2; i++) {
		fprintf(cfg, "%c%d", datos.flota[4].casillas[i].fila, datos.flota[4].casillas[i].columna);
		if (i != 1) fprintf(cfg, ",");
	}
	fprintf(cfg, "\n");

	fprintf(cfg, "submari ");
	for (i = 0; i < 4; i++) {
		fprintf(cfg, "%c%d", datos.flota[5+i].casillas[0].fila, datos.flota[5+i].casillas[0].columna);
		if (i != 3) fprintf(cfg, ",");
	}
	fprintf(cfg, "\n");

	fclose(cfg);

}

void eliminarConfig(juego *datos) {

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

void carregarConfig(juego *datos) {

	FILE *cfg;

	cfg = fopen("cfg.txt", "r+");
	char cadena[200], letra, cordenades[4][4];
	int numero, i, cont;

	//Taulell - fread(cadena, sizeof(char), 14, cfg);
	fgets(cadena, 81, cfg);
	datos->tablero.filas = atoi(&cadena[7]);
	datos->tablero.columnas = atoi(&cadena[11]);

	omplirTaulell(datos);

	//Portavions - fread(cadena, sizeof(char), 27, cfg);
	fgets(cadena, 81, cfg);
	cont = primerEspai(cadena) + 1;
	for (i = 0; i < 4; i++) {
		letra = toupper(cadena[cont]);
		numero = atoi(&cadena[cont+1]);
		datos->portavions[i].fila = letra;
		datos->portavions[i].columna = numero;
		cont = cont + 2 + digitsNumero(numero);
		sprintf(cordenades[i], "%c%d", letra, numero);
	}
	marcarTaulell(datos, cordenades, 4);

	//DestructorA - fread(cadena, sizeof(char), 23, cfg);
	fgets(cadena, 81, cfg);
	cont = primerEspai(cadena) + 1;
	for (i = 0; i < 3; i++) {
		letra = toupper(cadena[cont]);
		numero = atoi(&cadena[cont+1]);
		datos->destructorA[i].fila = letra;
		datos->destructorA[i].columna = numero;
		cont = cont + 2 + digitsNumero(numero);
		sprintf(cordenades[i], "%c%d", letra, numero);
	}
	marcarTaulell(datos, cordenades, 3);

	//DestructorB - fread(cadena, sizeof(char), 23, cfg);
	fgets(cadena, 81, cfg);
	cont = primerEspai(cadena) + 1;
	for (i = 0; i < 3; i++) {
		letra = toupper(cadena[cont]);
		numero = atoi(&cadena[cont+1]);
		datos->destructorB[i].fila = letra;
		datos->destructorB[i].columna = numero;
		cont = cont + 2 + digitsNumero(numero);
		sprintf(cordenades[i], "%c%d", letra, numero);
	}
	marcarTaulell(datos, cordenades, 3);

	//FragataA - fread(cadena, sizeof(char), 15, cfg);
	fgets(cadena, 81, cfg);
	cont = primerEspai(cadena) + 1;
	for (i = 0; i < 2; i++) {
		letra = toupper(cadena[cont]);
		numero = atoi(&cadena[cont+1]);
		datos->fragataA[i].fila = letra;
		datos->fragataA[i].columna = numero;
		cont = cont + 2 + digitsNumero(numero);
		sprintf(cordenades[i], "%c%d", letra, numero);
	}
	marcarTaulell(datos, cordenades, 2);

	//FragataB - fread(cadena, sizeof(char), 15, cfg);
	fgets(cadena, 81, cfg);
	cont = primerEspai(cadena) + 1;
	for (i = 0; i < 2; i++) {
		letra = toupper(cadena[cont]);
		numero = atoi(&cadena[cont+1]);
		datos->fragataB[i].fila = letra;
		datos->fragataB[i].columna = numero;
		cont = cont + 2 + digitsNumero(numero);
		sprintf(cordenades[i], "%c%d", letra, numero);
	}
	marcarTaulell(datos, cordenades, 2);

	//Submarins - fread(cadena, sizeof(char), 23, cfg);
	fgets(cadena, 81, cfg);
	cont = primerEspai(cadena) + 1;
	for (i = 0; i < 4; i++) {
		letra = toupper(cadena[cont]);
		numero = atoi(&cadena[cont+1]);
		datos->submarins[i][0].fila = letra;
		datos->submarins[i][0].columna = numero;
		cont = cont + 2 + digitsNumero(numero);
		sprintf(cordenades[0], "%c%d", letra, numero);
		marcarTaulell(datos, cordenades, 1);
	}


	fclose(cfg);

}

void crearConfig(juego *datos) {

	char cordenada[3];
	int alineacio;

	printf("\nCreació del fitxer de configuració");

	printf("\n\nCreació del Taulell\n");
	do {
		printf("Entra el numero de filas: ");
		scanf("%d", &datos->files);
	} while(datos->files < 0 || datos->files > MAX);

	do {
		printf("Entra el numero de columnas: ");
		scanf("%d", &datos->columnes);
	} while(datos->columnes < 0 || datos->columnes > MAX);

	printf("\n\nInicialitzant el taulell...");
	omplirTaulell(datos);

	printf("\n\nCreació de les embarcacions!\n");

	do {

		printf("\nPortavions");
		printf("\nEntra la cordenada icinal: ");
		scanf("%s", cordenada);
		printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal | 3 - Diagonal Inversa)\n\n\tOpció: ");
		scanf("%d", &alineacio);

	} while(!comprovaEmbarcacio(datos, cordenada, 4, alineacio, 0));
	imprimirTaulell(*datos);

	do {

		printf("\nDestructor A");
		printf("\nEntra la cordenada icinal: ");
		scanf("%s", cordenada);
		printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal | 3 - Diagonal Inversa)\n\n\tOpció: ");
		scanf("%d", &alineacio);

	} while(!comprovaEmbarcacio(datos, cordenada, 3, alineacio, 1));
	imprimirTaulell(*datos);

	do {

		printf("\nDestructor B");
		printf("\nEntra la cordenada icinal: ");
		scanf("%s", cordenada);
		printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal | 3 - Diagonal Inversa)\n\n\tOpció: ");
		scanf("%d", &alineacio);

	} while(!comprovaEmbarcacio(datos, cordenada, 3, alineacio, 2));
	imprimirTaulell(*datos);

	do {

		printf("\nFragata A");
		printf("\nEntra la cordenada icinal: ");
		scanf("%s", cordenada);
		printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal | 3 - Diagonal Inversa)\n\n\tOpció: ");
		scanf("%d", &alineacio);

	} while(!comprovaEmbarcacio(datos, cordenada, 2, alineacio, 3));
	imprimirTaulell(*datos);

	do {

		printf("\nFragata B");
		printf("\nEntra la cordenada icinal: ");
		scanf("%s", cordenada);
		printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal | 3 - Diagonal Inversa)\n\n\tOpció: ");
		scanf("%d", &alineacio);

	} while(!comprovaEmbarcacio(datos, cordenada, 2, alineacio, 4));
	imprimirTaulell(*datos);

	do {

		printf("\nSubmari A");
		printf("\nEntra la cordenada: ");
		scanf("%s", cordenada);

	} while(!comprovaEmbarcacio(datos, cordenada, 1, 0, 5));
	imprimirTaulell(*datos);

	do {

		printf("\nSubmari B");
		printf("\nEntra la cordenada: ");
		scanf("%s", cordenada);

	} while(!comprovaEmbarcacio(datos, cordenada, 1, 0, 6));
	imprimirTaulell(*datos);

	do {

		printf("\nSubmari C");
		printf("\nEntra la cordenada: ");
		scanf("%s", cordenada);

	} while(!comprovaEmbarcacio(datos, cordenada, 1, 0, 7));
	imprimirTaulell(*datos);

	do {

		printf("\nSubmari D");
		printf("\nEntra la cordenada: ");
		scanf("%s", cordenada);

	} while(!comprovaEmbarcacio(datos, cordenada, 1, 0, 8));
	imprimirTaulell(*datos);


	guardarConfig(*datos);

}

void modificarConfig(juego *datos) {

	int op, aux, auxAnterior;
	char cordenada[4];

	printf("\n\n\n ");

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

			auxAnterior = datos->files;

			datos->files = aux;

			if (marcaNoModificats(datos, op) == TRUE) printf("\n\t\tFiles modificades amb éxit!\n");
			else {
				datos->files = auxAnterior;
				printf("\n\t\tError al fer la modificació!\n");
			}

			break;
		case 2:

			printf("\n\n\tEntra les columnes del taulell: ");
			scanf("%d", &aux);

			auxAnterior = datos->columnes;
			datos->columnes = aux;

			if (marcaNoModificats(datos, op) == TRUE) printf("\n\t\tColumnes modificades amb éxit!\n");
			else {
				datos->columnes = auxAnterior;
				printf("\n\t\tError al fer la modificació!\n");
			}

			break;
		case 3:

			printf("\nPortavions");
			printf("\nEntra la cordenada icinal: ");
			scanf("%s", cordenada);
			printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal | 3 - Diagonal Inversa)\n\n\tOpció: ");
			scanf("%d", &aux);

			if (marcaNoModificats(datos, op) == TRUE) {
				if (comprovaEmbarcacio(datos, cordenada, 4, aux, 0)) printf("\n\t\tPortavions modificat amb éxit!\n");
				else printf("\n\t\tError al fer la modificació!\n");
			}

			break;
		case 4:

			printf("\nDestructorA");
			printf("\nEntra la cordenada icinal: ");
			scanf("%s", cordenada);
			printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal | 3 - Diagonal Inversa)\n\n\tOpció: ");
			scanf("%d", &aux);

			if (marcaNoModificats(datos, op) == TRUE) {
				if (comprovaEmbarcacio(datos, cordenada, 3, aux, 1)) printf("\n\t\tDestructorA modificat amb éxit!\n");
				else printf("\n\t\tError al fer la modificació!\n");
			}

			break;
		case 5:

			printf("\nDestructorB");
			printf("\nEntra la cordenada icinal: ");
			scanf("%s", cordenada);
			printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal | 3 - Diagonal Inversa)\n\n\tOpció: ");
			scanf("%d", &aux);

			if (marcaNoModificats(datos, op) == TRUE) {
				if (comprovaEmbarcacio(datos, cordenada, 3, aux, 2)) printf("\n\t\tDestructorB modificat amb éxit!\n");
				else printf("\n\t\tError al fer la modificació!\n");
			}

			break;
		case 6:

			printf("\nFragataA");
			printf("\nEntra la cordenada icinal: ");
			scanf("%s", cordenada);
			printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal | 3 - Diagonal Inversa)\n\n\tOpció: ");
			scanf("%d", &aux);

			if (marcaNoModificats(datos, op) == TRUE) {
				if (comprovaEmbarcacio(datos, cordenada, 2, aux, 3)) printf("\n\t\tFragataA modificat amb éxit!\n");
				else printf("\n\t\tError al fer la modificació!\n");
			}

			break;
		case 7:

			printf("\nFragataB");
			printf("\nEntra la cordenada icinal: ");
			scanf("%s", cordenada);
			printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal | 3 - Diagonal Inversa)\n\n\tOpció: ");
			scanf("%d", &aux);

			if (marcaNoModificats(datos, op) == TRUE) {
				if (comprovaEmbarcacio(datos, cordenada, 2, aux, 4)) printf("\n\t\tFragataB modificat amb éxit!\n");
				else printf("\n\t\tError al fer la modificació!\n");
			}

			break;
		case 8:

			printf("\nSubmariA");
			printf("\nEntra la cordenada: ");
			scanf("%s", cordenada);

			if (marcaNoModificats(datos, op) == TRUE) {
				if (comprovaEmbarcacio(datos, cordenada, 1, aux, 5)) printf("\n\t\tSubmariA modificat amb éxit!\n");
				else printf("\n\t\tError al fer la modificació!\n");
			}

			break;
		case 9:

			printf("\nSubmariB");
			printf("\nEntra la cordenada: ");
			scanf("%s", cordenada);

			if (marcaNoModificats(datos, op) == TRUE) {
				if (comprovaEmbarcacio(datos, cordenada, 1, aux, 6)) printf("\n\t\tSubmariB modificat amb éxit!\n");
				else printf("\n\t\tError al fer la modificació!\n");
			}

			break;
		case 10:

			printf("\nSubmariC");
			printf("\nEntra la cordenada: ");
			scanf("%s", cordenada);

			if (marcaNoModificats(datos, op) == TRUE) {
				if (comprovaEmbarcacio(datos, cordenada, 1, aux, 7)) printf("\n\t\tSubmariC modificat amb éxit!\n");
				else printf("\n\t\tError al fer la modificació!\n");
			}

			break;
		case 11:

			printf("\nSubmariD");
			printf("\nEntra la cordenada: ");
			scanf("%s", cordenada);

			if (marcaNoModificats(datos, op) == TRUE) {
				if (comprovaEmbarcacio(datos, cordenada, 1, aux, 8)) printf("\n\t\tSubmariD	 modificat amb éxit!\n");
				else printf("\n\t\tError al fer la modificació!\n");
			}

			break;
	}

	guardarConfig(*datos);

}

boolean marcaNoModificats(juego *datos, int op) {

	int i;
	char cordenades[4][4];
	boolean correcte = TRUE;

	omplirTaulell(datos);


	if (op != 3 && correcte) {
		for (i = 0; i < 4; i++) snprintf(cordenades[i], sizeof(cordenades[i]), "%c%d", datos->portavions[i].fila, datos->portavions[i].columna);
		correcte = comprovaEmbarcacio(datos, cordenades[0], 4, getAlineacio(cordenades, 4), 0);
	}
	if (op != 4 && correcte) {
		for (i = 0; i < 3; i++) sprintf(cordenades[i], "%c%d", datos->destructorA[i].fila, datos->destructorA[i].columna);
		correcte = comprovaEmbarcacio(datos, cordenades[0], 3, getAlineacio(cordenades, 3), 1);
	}
	if (op != 5 && correcte) {
		for (i = 0; i < 3; i++) sprintf(cordenades[i], "%c%d", datos->destructorB[i].fila, datos->destructorB[i].columna);
		correcte = comprovaEmbarcacio(datos, cordenades[0], 3, getAlineacio(cordenades, 3), 2);
	}
	if (op != 6 && correcte) {
		for (i = 0; i < 2; i++) sprintf(cordenades[i], "%c%d", datos->fragataA[i].fila, datos->fragataA[i].columna);
		correcte = comprovaEmbarcacio(datos, cordenades[0], 2, getAlineacio(cordenades, 2), 3);
	}
	if (op != 7 && correcte) {
		for (i = 0; i < 2; i++) sprintf(cordenades[i], "%c%d", datos->fragataB[i].fila, datos->fragataB[i].columna);
		correcte = comprovaEmbarcacio(datos, cordenades[0], 2, getAlineacio(cordenades, 2), 4);
	}
	if (op != 8 && correcte) {
		sprintf(cordenades[0], "%c%d", datos->submarins[0][0].fila, datos->submarins[0][0].columna);
		correcte = comprovaEmbarcacio(datos, cordenades[0], 1, getAlineacio(cordenades, 1), 5);
	}
	if (op != 9 && correcte) {
		sprintf(cordenades[0], "%c%d", datos->submarins[1][0].fila, datos->submarins[1][0].columna);
		correcte = comprovaEmbarcacio(datos, cordenades[0], 1, getAlineacio(cordenades, 1), 6);
	}
	if (op != 10 && correcte) {
		sprintf(cordenades[0], "%c%d", datos->submarins[2][0].fila, datos->submarins[2][0].columna);
		correcte = comprovaEmbarcacio(datos, cordenades[0], 1, getAlineacio(cordenades, 1), 7);
	}
	if (op != 11 && correcte) {
		sprintf(cordenades[0], "%c%d", datos->submarins[3][0].fila, datos->submarins[3][0].columna);
		correcte = comprovaEmbarcacio(datos, cordenades[0], 1, getAlineacio(cordenades, 1), 8);
	}

	return correcte;

}


boolean comprovaEmbarcacio(juego *datos, char cordenada[4], int mida, int alineacio, int embarcacio) {

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
		if (getFila(cordenades[i]) > 'A' + datos->files) correcte = FALSE;
		if (getColumna(cordenades[i])  > datos->columnes) correcte = FALSE;
		if (datos->taulell[getFila(cordenades[i]) - 'A'][getColumna(cordenades[i])] != '-') correcte = FALSE;

	}

	if (correcte) {
		marcarTaulell(datos, cordenades, mida);
		marcarStruct(datos, cordenades, mida, embarcacio);
	}

	return correcte;

}


void marcarTaulell(juego *datos, char cordenades[4][4], int mida) {

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

		datos->taulell[getFila(cordenades[i])-'A'][getColumna(cordenades[i]) - 1] = lletra;

	}

}

void marcarStruct(juego *datos, char cordenades[4][4], int mida, int embarcacio) {

	int i = 0;
	for (i = 0; i < mida; i++) {

		switch(embarcacio) {
			case 0:
				datos->portavions[i].fila = getFila(cordenades[i]);
				datos->portavions[i].columna = getColumna(cordenades[i]);
			break;
			case 1:
				datos->destructorA[i].fila = getFila(cordenades[i]);
				datos->destructorA[i].columna = getColumna(cordenades[i]);
			break;
			case 2:
				datos->destructorB[i].fila = getFila(cordenades[i]);
				datos->destructorB[i].columna = getColumna(cordenades[i]);
			break;
			case 3:
				datos->fragataA[i].fila = getFila(cordenades[i]);
				datos->fragataA[i].columna = getColumna(cordenades[i]);
			break;
			case 4:
				datos->fragataB[i].fila = getFila(cordenades[i]);
				datos->fragataB[i].columna = getColumna(cordenades[i]);
			break;
			case 5:
				datos->submarins[0][i].fila = getFila(cordenades[i]);
				datos->submarins[0][i].columna = getColumna(cordenades[i]);
			break;
			case 6:
				datos->submarins[1][i].fila = getFila(cordenades[i]);
				datos->submarins[1][i].columna = getColumna(cordenades[i]);
			break;
			case 7:
				datos->submarins[2][i].fila = getFila(cordenades[i]);
				datos->submarins[2][i].columna = getColumna(cordenades[i]);
			break;
			case 8:
				datos->submarins[3][i].fila = getFila(cordenades[i]);
				datos->submarins[3][i].columna = getColumna(cordenades[i]);
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


int primerEspai(char cad[100]) {

	int i, espai = -1;

	for (i = 0; i < strlen(cad) && espai == -1; i++) {
		if (cad[i] == ' ') espai = i;
	}

	return espai;

}

int getMidaBarco(char lletra) {

	int mida;

	switch(lletra) {
	case 'P':
		mida = 4;
		break;
	case 'D':
		mida = 3;
		break;
	case 'F':
		mida = 2;
		break;
	case 'D':
		mida = 1;
		break;
	}

	return mida;
}

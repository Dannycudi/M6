/*
 ============================================================================
 Name        : HundirLaFloota.c
 Author      : Dannycudi
 Version     : 1.0
 Copyright   : Dannycudi
 Description : Juego de hundir la flota.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "boolean.h"

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
};

// Mirar si es posible haciendo una estructura para cada tipo de barco
// y generar una estructura madre que contenga cada una de las diferentes estructuras de barco.
typedef struct Joc joc;

void mostrarConfig(joc dades);
void carregarConfig(joc *dades);
void crearConfig(joc *dades);
void imprimirTaulell();
int digitsNumero(int numero);
int midaFitxer(char *f);
int opcioMeu();
char getColumna(char cad[10]);
int getFila(char cad[10]);
boolean posicioValida(char cad[10]);

int main(void) {

	joc dades;

	if (midaFitxer("cfg.txt")) carregarConfig(&dades);
	else crearConfig(&dades);

	mostrarConfig(dades);

	int op;

	do {
		op = 1;
		//op = opcioMenu();

	} while(op < 1 || op > 6);

	return 0;

}

void imprimirTaulell() {



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

char getColumna(char cad[10]) {

	return cad[0];

}

int getFila(char cad[10]) {

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

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
	cordenada submariA[1];
	cordenada submariB[1];
	cordenada submariC[1];
	cordenada submariD[1];
};

// Mirar si es posible haciendo una estructura para cada tipo de barco
// y generar una estructura madre que contenga cada una de las diferentes estructuras de barco.
typedef struct Joc joc;

void carregarConfig(joc *dades);
void imprimirTaulell();
int digitsNumero(int numero);
int opcioMeu();
char getColumna(char cad[10]);
int getFila(char cad[10]);
boolean posicioValida(char cad[10]);

int main(void) {
	joc dades;
	cordenada cord;
	carregarConfig(&dades);
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

	int op;

	do {
		op = 1;
		//op = opcioMenu();

	} while(op < 1 || op > 6);

	return 0;

}

void imprimirTaulell() {



}

void carregarConfig(joc *dades) {

	FILE *cfg;
	long int mida;

	cfg = fopen("cfg.txt", "a+");
	fseek(cfg, 0L, SEEK_END);
	mida=ftell(cfg);
	fclose(cfg);

	if (mida == 0) printf("S'ha de crear la configuració.");
	else {

		cfg = fopen("cfg.txt", "r+");
		char cadena[200], letra;
		int numero, i, cont;
		cordenada cord;

//		while (!feof(cfg))
//		{
			fread(cadena, sizeof(char), 14, cfg);
			dades->columnes = atoi(&cadena[11]);
			dades->files = atoi(&cadena[7]);

			//Portavions
			fread(cadena, sizeof(char), 27, cfg);
			cont = 11;
			for (i = 0; i < 4; i++) {
				letra = cadena[cont];
				numero = atoi(&cadena[cont+1]);
				dades->portavions[i].fila = letra;
				dades->portavions[i].columna = numero;
				cont = cont + 2 + digitsNumero(numero);
			}

			//DestructorA
			fread(cadena, sizeof(char), 23, cfg);
			cont = 12;
			for (i = 0; i < 3; i++) {
				letra = cadena[cont];
				numero = atoi(&cadena[cont+1]);
				dades->destructorA[i].fila = letra;
				dades->destructorA[i].columna = numero;
				cont = cont + 2 + digitsNumero(numero);
			}

			//DestructorB
			fread(cadena, sizeof(char), 23, cfg);
			cont = 13;
			for (i = 0; i < 3; i++) {
				letra = cadena[cont];
				numero = atoi(&cadena[cont+1]);
				dades->destructorB[i].fila = letra;
				dades->destructorB[i].columna = numero;
				cont = cont + 2 + digitsNumero(numero);
			}

//		}

		fclose(cfg);
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

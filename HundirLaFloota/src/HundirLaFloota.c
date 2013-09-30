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

struct Joc
{
	char files[3];
	char columnes[3];
	char portavions[15];
	char destructorA[11];
	char destructorB[11];
	char fragataA[7];
	char fragataB[7];
	char submariA[3];
	char submariB[3];
	char submariC[3];
	char submariD[3];
};

void carregarConfig();
int opcioMeu();
char getColumna(char cad[10]);
int getFila(char cad[10]);
boolean posicioValida(char cad[10]);

int main(void) {

	carregarConfig();
	int op;

	do {

		op = opcioMenu();

	} while(op < 1 || op > 6);

	return 0;

}

void carregarConfig() {

	FILE *cfg;
	long int mida;

	cfg = fopen("cfg.txt", "a+");
	fseek(cfg, 0L, SEEK_END);
	mida=ftell(cfg);
	fclose(cfg);

	if (mida == 0) printf("S'ha de crear la configuració.");
	else {

		cfg = fopen("cfg.txt", "r+");
		char cadena[100];

		while (!feof(cfg))
		{
			fread(cadena, sizeof(char), 100, cfg);
			printf("%s\n", cadena);
		}

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

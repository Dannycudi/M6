/*
 ============================================================================
 Name        : HundirLaFloota.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "boolean.h"

char getColumna(char cad[10]);
int getFila(char cad[10]);
boolean posicioValida(char cad[10]);

int main(void) {

	char posicio[10] = "AC15";
	char columna = getColumna(posicio);
	int fila = getFila(posicio);

	if (posicioValida(posicio)) printf("%c - %d", columna, fila);
	else printf("La posició no es vàlida!");

	return 0;

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

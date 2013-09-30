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

int main(void) {

	char columna = getColumna("A15");
	int fila = getFila("A15");

	printf("%c - %d", columna, fila);

	return 0;

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

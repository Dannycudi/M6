/*
 ============================================================================
 Name        : HundirLaFlota-Colores.c
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
#include <unistd.h>
#include <sys/wait.h>

#define MAX 25

/* Colores Linux
	Negro       0;30     Gris Obscuro  1;30		Subrayado Negro 	4;30
	Azul        0;34     Azul Claro    1;34
	Verde       0;32     Verde Claro   1;32
	Cyan        0;36     Cyan Claro    1;36
	Rojo        0;31     Rojo Claro    1;31
	Purpura     0;35     Fiuscha       1;35
	Café        0;33     Amarillo      1;33
	Gris Claro  0;37     Blanco        1;37
 */

#define BLANCO "\e[m"
#define ROJO "\e[31m"
#define ROJOCLARO "\e[1;31m"
#define VERDE "\e[32m"
#define VERDECLARO "\e[1;32m"
#define CAFE "\e[33m"
#define AMARILLO "\e[1;33m"
#define AZUL "\e[34m"
#define MAGENTA "\e[35m"
#define FUCSIA "\e[1;35m"
#define CYAN "\e[36m"
#define CYANCLARO "\e[1;36m"

#define BLANCO_S "\e[4m"

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
char getInicialBarco(int num);
void rellenarNombres();
void canviarArxiu();
void canviarTurno();
void opcioJugador();

char casillas[MAX][MAX], nombres[9][20], arxiu[50];
char casillasJ1[MAX][MAX], casillasJ2[MAX][MAX], resultadosJ1[MAX][MAX], resultadosJ2[MAX][MAX];
int turno = 1;

int main(void) {

	int op;
	juego datos;
	rellenarNombres();
	strcpy(arxiu, "cfg.dat");

	datos.tablero.filas = -1;
	datos.tablero.columnas = -1;

	opcioJugador();

	do {
		op = opcioMenu();

		switch(op) {

		case 1:

			canviarArxiu();
			if (midaFitxer(arxiu)) {
				carregarConfig(&datos);
				imprimirTaulell(datos);
				printf("\n\n\t"VERDECLARO"Fitxer de configuració '%s' carregat amb éxit!\n\n"BLANCO, arxiu);
			}
			else printf(ROJO"\n\tNo s'ha pogut carregar el fitxer de configuració '%s'."BLANCO, arxiu);
			break;

		case 2:

			canviarArxiu();
			crearConfig(&datos);
			printf(VERDE"\n\n\tFitxer de configuració creat amb éxit. %s!\n"BLANCO, arxiu);
			break;

		case 3:

			canviarArxiu();
			if (midaFitxer(arxiu) && (datos.tablero.columnas != -1 && datos.tablero.filas != -1)) {
				modificarConfig(&datos);
				carregarConfig(&datos); //TODO: Mirar de arreglarlo, no debería hacer falta.
			}
			else printf(ROJO"\n\n\t\tNo es troba una configuració a modificar.\n\t\tIntenta llegir o crear-la abans.\n\n"BLANCO);
			break;

		case 4:

			canviarArxiu();
			if (midaFitxer(arxiu) && (datos.tablero.columnas != -1 && datos.tablero.filas != -1)) {
				eliminarConfig(&datos);
			}
			else printf(ROJO"\n\n\t\tNo es troba una configuració a eliminar.\n\t\tIntenta llegir o crear-la abans.\n\n"BLANCO);
			break;

		case 5:

			canviarArxiu();
			if (midaFitxer(arxiu)) {// && (datos.tablero.columnas != -1 && datos.tablero.filas != -1)) {
				mostrarConfig(datos);
			}
			else printf(ROJO"\n\n\t\tNo es troba una configuració a mostrar.\n\t\tIntenta llegir o crear-la abans.\n\n"BLANCO);
			break;

		case 6:
			canviarArxiu();
			break;

		case 7:
			opcioJugador();
			system("clear");
			break;
		}

		printf("\n\n");

	} while(op != 9);


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
	printf("\n\n\n\t    "BLANCO_S" ");
	for (i = 0; i < datos.tablero.columnas; i++) {
		if (i == 0) printf("%d ", i + 1);
		else if (i < 10) printf(" %d ", i + 1);
		else printf("%d ", i + 1);
	}
	printf(BLANCO"\n");
	for (i = 0; i < datos.tablero.filas; i++) {
		printf("\t %c %c", i + 'A', 124);
		for (j = 0; j < datos.tablero.columnas; j++) {
			switch(casillas[i][j]) {
			case '-':
				printf(CYAN" %c "BLANCO, casillas[i][j]);
				break;
			case 'P':
				printf(AMARILLO" %c "BLANCO, casillas[i][j]);
				break;
			case 'F':
				printf(VERDECLARO" %c "BLANCO, casillas[i][j]);
				break;
			case 'D':
				printf(FUCSIA" %c "BLANCO, casillas[i][j]);
				break;
			case 'S':
				printf(ROJOCLARO" %c "BLANCO, casillas[i][j]);
				break;
			default:
				printf(" %c ", casillas[i][j]);
			}

		}
		printf("\n");
	}

}

void mostrarConfig(juego datos) {

	int i;

	printf("\tTaulell\n\t\tFiles - %d \t Columnes - %d\n", datos.tablero.filas, datos.tablero.columnas);

	printf("\n\tPortavions\n");
	for (i = 0; i < 4; i++) {
		printf("\t\tFila - %c \t Columna - %d\n", datos.flota[0].casillas[i].fila + 'A', datos.flota[0].casillas[i].columna);
	}
	printf("\n\tDestructorA\n");
	for (i = 0; i < 3; i++) {
		printf("\t\tFila - %c \t Columna - %d\n", datos.flota[1].casillas[i].fila + 'A', datos.flota[1].casillas[i].columna);
	}
	printf("\n\tDestructorB\n");
	for (i = 0; i < 3; i++) {
		printf("\t\tFila - %c \t Columna - %d\n", datos.flota[2].casillas[i].fila + 'A', datos.flota[2].casillas[i].columna);
	}
	printf("\n\tFragataA\n");
	for (i = 0; i < 2; i++) {
		printf("\t\tFila - %c \t Columna - %d\n", datos.flota[3].casillas[i].fila + 'A', datos.flota[3].casillas[i].columna);
	}
	printf("\n\tFragataB\n");
	for (i = 0; i < 2; i++) {
		printf("\t\tFila - %c \t Columna - %d\n", datos.flota[4].casillas[i].fila + 'A', datos.flota[4].casillas[i].columna);
	}
	printf("\n\tSubmarins\n");
	for (i = 0; i < 4; i++) {
		printf("\t\tFila - %c \t Columna - %d\n", datos.flota[5+i].casillas[0].fila + 'A', datos.flota[5+i].casillas[0].columna);
	}

	imprimirTaulell(datos);

}

void guardarConfig(juego datos) {

	FILE *cfg;

	cfg = fopen(arxiu, "w+b");

	fwrite(&datos, sizeof(datos), 1, cfg);

	//printf("%d", (int)ftell(cfg));

	fclose(cfg);

}

void eliminarConfig(juego *datos) {

	char op;

	printf(CAFE"\n\tLa configuración actual está a punto de eliminarse. "BLANCO);
	do {
		printf("\n\n\t\t¿Estás seguro? (s/n): "VERDE);
		getchar();
		scanf("%c", &op);
		printf(BLANCO);
	}
	while(op != 's' && op != 'n' && op != 'S' && op != 'N');

	if (op == 's' || op == 'S') {
		remove("cfg.txt");
		printf(VERDECLARO"\n\t\tFitxer 'cfg.txt' de configuració eliminat amb éxit!\n"BLANCO);
	}

}

void carregarConfig(juego *datos) {

	FILE *cfg;
	char cordenades[4][4];
	int i, j;
	pid_t hijo;

	if ((hijo=vfork()) == 0) {
		cfg = fopen(arxiu, "r+b");
		fread(datos, sizeof(juego), 1, cfg);
		fclose(cfg);
		_exit(0);
	}
	else {
		hijo=wait(&i);
		printf("Exit del hijo %d: %d", hijo, i);
	}

	omplirTaulell(datos);

	for (i = 0; i < 9; i++) {
		for (j = 0; j < getMidaBarco(datos->flota[i].tipo); j++) {
			sprintf(cordenades[j], "%c%d", datos->flota[i].casillas[j].fila + 'A', datos->flota[i].casillas[j].columna);
		}
		marcarTaulell(datos, cordenades, getMidaBarco(datos->flota[i].tipo));
	}



}

void crearConfig(juego *datos) {

	char cordenada[3];
	int alineacio, i;

	printf("\nCreació del fitxer de configuració");

	printf("\n\nCreació del Taulell\n");
	do {
		printf("Entra el numero de filas: ");
		scanf("%d", &datos->tablero.filas);
	} while(datos->tablero.filas < 0 || datos->tablero.filas > MAX);

	do {
		printf("Entra el numero de columnas: ");
		scanf("%d", &datos->tablero.columnas);
	} while(datos->tablero.columnas < 0 || datos->tablero.columnas > MAX);

	printf("\n\nInicialitzant el taulell...");
	omplirTaulell(datos);

	printf("\n\nCreació de les embarcacions!\n");

	for (i = 0; i < 9; i++) {
		do {

			printf("\n%s", nombres[i]);
			printf("\nEntra la cordenada icinal: ");
			scanf("%s", cordenada);
			if (i < 5) {
				printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal | 3 - Diagonal Inversa)\n\n\tOpció: ");
				scanf("%d", &alineacio);
			}
			else alineacio = 0;

		} while(!comprovaEmbarcacio(datos, cordenada, getMidaBarco(getInicialBarco(i)), alineacio, i));
		imprimirTaulell(*datos);
	}


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

			auxAnterior = datos->tablero.filas;

			datos->tablero.filas = aux;

			if (marcaNoModificats(datos, op) == TRUE) printf(VERDE"\n\t\tFiles modificades amb éxit!\n"BLANCO);
			else {
				datos->tablero.filas = auxAnterior;
				printf(ROJO"\n\t\tError al fer la modificació!\n"BLANCO);
			}

			break;
		case 2:

			printf("\n\n\tEntra les columnes del taulell: ");
			scanf("%d", &aux);

			auxAnterior = datos->tablero.columnas;
			datos->tablero.columnas = aux;

			if (marcaNoModificats(datos, op) == TRUE) printf(VERDE"\n\t\tColumnes modificades amb éxit!\n"BLANCO);
			else {
				datos->tablero.columnas = auxAnterior;
				printf(ROJO"\n\t\tError al fer la modificació!\n"BLANCO);
			}

			break;
		case 3:

			printf("\nPortavions");
			printf("\nEntra la cordenada icinal: ");
			scanf("%s", cordenada);
			printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal | 3 - Diagonal Inversa)\n\n\tOpció: ");
			scanf("%d", &aux);

			if (marcaNoModificats(datos, op) == TRUE) {
				if (comprovaEmbarcacio(datos, cordenada, 4, aux, 0)) printf(VERDE"\n\t\tPortavions modificat amb éxit!\n"BLANCO);
				else printf(ROJO"\n\t\tError al fer la modificació!\n"BLANCO);
			}

			break;
		case 4:

			printf("\nDestructorA");
			printf("\nEntra la cordenada icinal: ");
			scanf("%s", cordenada);
			printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal | 3 - Diagonal Inversa)\n\n\tOpció: ");
			scanf("%d", &aux);

			if (marcaNoModificats(datos, op) == TRUE) {
				if (comprovaEmbarcacio(datos, cordenada, 3, aux, 1)) printf(VERDE"\n\t\tDestructorA modificat amb éxit!\n"BLANCO);
				else printf(ROJO"\n\t\tError al fer la modificació!\n"BLANCO);
			}

			break;
		case 5:

			printf("\nDestructorB");
			printf("\nEntra la cordenada icinal: ");
			scanf("%s", cordenada);
			printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal | 3 - Diagonal Inversa)\n\n\tOpció: ");
			scanf("%d", &aux);

			if (marcaNoModificats(datos, op) == TRUE) {
				if (comprovaEmbarcacio(datos, cordenada, 3, aux, 2)) printf(VERDE"\n\t\tDestructorB modificat amb éxit!\n"BLANCO);
				else printf(ROJO"\n\t\tError al fer la modificació!\n"BLANCO);
			}

			break;
		case 6:

			printf("\nFragataA");
			printf("\nEntra la cordenada icinal: ");
			scanf("%s", cordenada);
			printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal | 3 - Diagonal Inversa)\n\n\tOpció: ");
			scanf("%d", &aux);

			if (marcaNoModificats(datos, op) == TRUE) {
				if (comprovaEmbarcacio(datos, cordenada, 2, aux, 3)) printf(VERDE"\n\t\tFragataA modificat amb éxit!\n"BLANCO);
				else printf(ROJO"\n\t\tError al fer la modificació!\n"BLANCO);
			}

			break;
		case 7:

			printf("\nFragataB");
			printf("\nEntra la cordenada icinal: ");
			scanf("%s", cordenada);
			printf("\nEntra l'alineació: (0 - Horitzontal | 1 - Vertical | 2 - Diagonal | 3 - Diagonal Inversa)\n\n\tOpció: ");
			scanf("%d", &aux);

			if (marcaNoModificats(datos, op) == TRUE) {
				if (comprovaEmbarcacio(datos, cordenada, 2, aux, 4)) printf(VERDE"\n\t\tFragataB modificat amb éxit!\n"BLANCO);
				else printf(ROJO"\n\t\tError al fer la modificació!\n"BLANCO);
			}

			break;
		case 8:

			printf("\nSubmariA");
			printf("\nEntra la cordenada: ");
			scanf("%s", cordenada);

			if (marcaNoModificats(datos, op) == TRUE) {
				if (comprovaEmbarcacio(datos, cordenada, 1, aux, 5)) printf(VERDE"\n\t\tSubmariA modificat amb éxit!\n"BLANCO);
				else printf(ROJO"\n\t\tError al fer la modificació!\n"BLANCO);
			}

			break;
		case 9:

			printf("\nSubmariB");
			printf("\nEntra la cordenada: ");
			scanf("%s", cordenada);

			if (marcaNoModificats(datos, op) == TRUE) {
				if (comprovaEmbarcacio(datos, cordenada, 1, aux, 6)) printf(VERDE"\n\t\tSubmariB modificat amb éxit!\n"BLANCO);
				else printf(ROJO"\n\t\tError al fer la modificació!\n"BLANCO);
			}

			break;
		case 10:

			printf("\nSubmariC");
			printf("\nEntra la cordenada: ");
			scanf("%s", cordenada);

			if (marcaNoModificats(datos, op) == TRUE) {
				if (comprovaEmbarcacio(datos, cordenada, 1, aux, 7)) printf(VERDE"\n\t\tSubmariC modificat amb éxit!\n"BLANCO);
				else printf(ROJO"\n\t\tError al fer la modificació!\n"BLANCO);
			}

			break;
		case 11:

			printf("\nSubmariD");
			printf("\nEntra la cordenada: ");
			scanf("%s", cordenada);

			if (marcaNoModificats(datos, op) == TRUE) {
				if (comprovaEmbarcacio(datos, cordenada, 1, aux, 8)) printf(VERDE"\n\t\tSubmariD modificat amb éxit!\n"BLANCO);
				else printf(ROJO"\n\t\tError al fer la modificació!\n"BLANCO);
			}

			break;
	}

	guardarConfig(*datos);

}

boolean marcaNoModificats(juego *datos, int op) {

	int i, j;
	char cordenades[4][4];
	boolean correcte = TRUE;

	omplirTaulell(datos);

	for (i = 0; i < 9 && correcte; i++) {
		if (op != i) {
			for (j = 0; j < getMidaBarco(datos->flota[i].tipo); j++) {
				snprintf(cordenades[j], sizeof(cordenades[j]), "%c%d", datos->flota[i].casillas[j].fila + 'A', datos->flota[i].casillas[j].columna);
			}
			correcte = comprovaEmbarcacio(datos, cordenades[0], getMidaBarco(datos->flota[i].tipo), getAlineacio(cordenades, getMidaBarco(datos->flota[i].tipo)), i);
		}
	}

	return correcte;

}


boolean comprovaEmbarcacio(juego *datos, char cordenada[4], int mida, int alineacio, int embarcacio) {

	//TODO: No hace falta pasar mida, se puede saber con el número de embarcación. getMidaBarco()

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

	printf("%s %d - \n", cordenada, embarcacio);
	for (i = 0; i < mida; i++) {

		if (!posicioValida(cordenades[i])) correcte = FALSE;
		printf("%d", correcte);
		if (getFila(cordenades[i]) > 'A' + datos->tablero.filas) correcte = FALSE;
		printf("%d", correcte);
		if (getColumna(cordenades[i]) > datos->tablero.columnas) correcte = FALSE;
		printf("%d", correcte);
		if (casillas[getFila(cordenades[i]) - 'A'][getColumna(cordenades[i]) -1] != '-') correcte = FALSE;
		printf("%d", correcte);
		printf("\n");
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

		casillas[getFila(cordenades[i])-'A'][getColumna(cordenades[i]) - 1] = lletra;

	}

}

void marcarStruct(juego *datos, char cordenades[4][4], int mida, int embarcacio) {

	//TODO: Quitar el parámetro mida, no es necesario teniendo la embarcació. getMidaBarco();

	int i = 0;
	datos->flota[embarcacio].tipo = getInicialBarco(embarcacio);
	for (i = 0; i < mida; i++) {

		datos->flota[embarcacio].casillas[i].fila = getFila(cordenades[i]) - 'A';
		datos->flota[embarcacio].casillas[i].columna = getColumna(cordenades[i]);

	}

}

void canviarArxiu() {

	printf(BLANCO"\n\n\tEntra el nom de l'arxiu de configuració: "CAFE);
	scanf("%s", arxiu);
	printf(BLANCO);

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
		printf(BLANCO_S"\n\n\tMENÚ PRINCIPAL\t\t\t"BLANCO CAFE"'Jugador %d'\n\n"BLANCO, turno);
		printf("\t"VERDE"1)"BLANCO" Llegir configuració\n\t"VERDE"2)"BLANCO" Crear configuració\n");
		printf("\t"VERDE"3)"BLANCO" Modificar configuració\n\t"VERDE"4)"BLANCO" Eliminar configuració\n");
		printf("\t"VERDE"5)"BLANCO" Mostra Configuració\n\t"VERDE"6)"BLANCO" Canviar arxiu de configuració\n");
		printf("\t"VERDE"7)"BLANCO" Canviar de Jugador\n\t"VERDE"8)"BLANCO" JUGAR!\n\t"VERDE"9)"BLANCO" Srotir");
		printf("\n\n\t\tOpció: "AMARILLO);
		scanf("%d", &op);
		printf(BLANCO);
	}
	while (op < 1 || op > 9);

	return op;
}

void opcioJugador() {

	int op;

	do {
		printf(BLANCO_S"\n\n\t¿QUIN JUGADOR?"BLANCO"\n\n\t"VERDE"Escull un jugador ("CAFE"1-2"VERDE"):"BLANCO);
		printf("\n\n\t\tJugador: "AMARILLO);
		scanf("%d", &op);
		printf(BLANCO);
	}
	while (op < 1 || op > 2);

	turno = op;

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
	case 'S':
		mida = 1;
		break;
	}

	return mida;
}

char getInicialBarco(int num) {

	return nombres[num][0];

}

void rellenarNombres() {

	strcpy(nombres[0], "Portavions");
	strcpy(nombres[1], "Destructor1");
	strcpy(nombres[2], "Destructor2");
	strcpy(nombres[3], "Fragata1");
	strcpy(nombres[4], "Fragata2");
	strcpy(nombres[5], "SubmariA");
	strcpy(nombres[6], "SubmariB");
	strcpy(nombres[7], "SubmariC");
	strcpy(nombres[8], "SubmariD");
}
void canviarTurno() {

	if (turno == 1) turno = 2;
	else turno = 1;

}

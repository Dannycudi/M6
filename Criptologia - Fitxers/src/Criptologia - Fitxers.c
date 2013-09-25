#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int op_menu();
int op_encriptar();

int main()
{

	char cad[100], cadAux[100];
	int quantitat;
	int i = 0, op = 0, opcio = 0;

	FILE *f;

	f = fopen("encriptats.txt", "a+");

	do {

		op = op_menu();

		// Switch Principal - Menú
		switch(op) {

			case 1: //Transposició
			{
				printf("\n\nTransposició!\n");
				opcio = op_encriptar();

				printf("\nCada quants caràcters? ");
				getchar();
				scanf("%d", &quantitat);
				int posicions[quantitat];
				int posicio = 0, actual = 0, longitud = 0;

				switch(opcio) //Encriptar o desencriptar?
				{
					case 1:
					{
						for (i = 0; i < quantitat; i++) {
							printf("\nEntra el %d dígit per l'ordre: ", i+1);
							scanf("%d", &posicions[i]);
						}

						printf("\nEntra la paraula a encriptar: ");
						getchar();
						gets(cad);

						if (strlen(cad) % quantitat == 0) longitud = strlen(cad);
						else longitud = strlen(cad) + (quantitat - (strlen(cad) % quantitat));

						for (i = 0; i < longitud; i++) {
							if (posicio >= quantitat) posicio = 0;

							actual = i - posicio + posicions[posicio] - 1;
							cadAux[actual] = cad[i];

							if (!isalpha(cadAux[actual]) && cadAux[actual] != ' ' && !isdigit(cadAux[actual])) cadAux[actual] = '-';

							posicio++;
						}

						cadAux[i] = '\0';
						puts(cadAux);

						fputs(cadAux, f);

						printf("\nEncriptació guardada amb éxit!");

					}
					break;
					case 2: {

						for (i = 0; i < quantitat; i++) {
							printf("\nEntra el %d dígit per l'ordre: ", i+1);
							scanf("%d", &posicions[i]);
						}

						printf("\nEntra la paraula a desencriptar: ");
						getchar();
						gets(cad);

						if (strlen(cad) % quantitat == 0) longitud = strlen(cad);
						else longitud = (strlen(cad) % quantitat) * quantitat;

						for (i = 0; i < longitud; i++) {
							if (posicio >= quantitat) posicio = 0;

							actual = i - posicio;
							cadAux[i] = cad[actual+posicions[posicio]-1];

							if (cadAux[i] == '-') cadAux[i] = ' ';

							posicio++;
						}

						cadAux[i] = '\0';
						puts(cadAux);
					} break;
				} //End Switch Encriptar - Desencriptar

			} break;
		} //End Swtich Menú

	} while (op != 5);

	fclose(f);

    return 0;
}

int op_menu() {

	int op = 0;

	do {
		printf("\nEscull una opció: ");
		printf("\n1 - Transposició\n2 - Substitució Simple\n3 - Substitució Homofónica\n4 - Substitució Polifabética\n5 - Sortir\n\n\tOpció: ");
		scanf("%d", &op);
	}
	while(op < 1 || op > 5);

	return op;

}

int op_encriptar() {

	int opcio;
	do {
		printf("\n Que vols? \n1- Encriptar\n2 - Desencriptar\nOpció: ");
		scanf("%d", &opcio);
	} while(opcio < 1 || opcio > 2);

	return opcio;

}

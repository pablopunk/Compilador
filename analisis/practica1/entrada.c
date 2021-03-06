
//
// Implementacion del sistema de entrada
//

// Librerias de C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Librerias propias
#include "entrada.h"
#include "errores.h"

#define N 4096		// tamanho de buffer
#define FILEMODE "r" 	// modo lectura de archivo

char* nombreArchivo;
char buffer1[N+1];
char buffer2[N+1];
int leyendoBuffer = 0; // buffer que estamos leyendo
int flag = 0; // esta a 1 si ya esta cargado el siguiente buffer
FILE* pFile = NULL; // puntero a archivo

char* inicio; // Puntero al inicio del lexema
char* delantero; // Puntero al caracter que estamos leyendo

// Devuelve 1 si estamos en el fin del fichero
int esFinDeFichero()
{
	if (feof(pFile)) {
    //printf("Cerrando archivo...\n");
		fclose(pFile); // Cerramos el archivo
		pFile = NULL; free(pFile);
		return 1;
	}

	return 0;
}

void cargarBuffer1()
{
	int leidos=0;
	leyendoBuffer = 0; // Actualizamos el ultimo buffer leido

	leidos = fread(buffer1, 1, N, pFile); // Leo N bytes(1) del archivo
	buffer1[leidos] = EOF; // Fin de fichero si leidos<N / si no, es el fin del buffer (centinela)

	// actualizo el puntero delantero
	delantero = buffer1;
}

void cargarBuffer2()
{
	int leidos=0;
	leyendoBuffer = 1; // Actualizamos el ultimo buffer leido

	leidos = fread(buffer2, 1, N, pFile); // Leo N bytes(1) del archivo
	buffer2[leidos] = EOF; // Fin de fichero si leidos<N / si no, es el fin del buffer (centinela)

	// actualizo el puntero delantero
	delantero = buffer2;
}

// Carga el buffer n
void cargarBuffer(int n)
{
	if (n == 1) cargarBuffer2();
	else cargarBuffer1();
}

// Funcion de lectura, devuelve 0 en caso de que no haya errores
int leerArchivo()
{
	// Abro el archivo en modo lectura
	if ( (pFile = fopen(nombreArchivo, FILEMODE)) == NULL ) {
		errorArchivo("Error al leer archivo\n", FILE_OPEN);
		return -1;
	}

	// Cargo el primer buffer
	cargarBuffer1();

	inicio = delantero = buffer1; // Inicio los punteros

	return 0;
}

// Inicializar el sistema de entrada
void inicializarEntrada(char* fichero)
{
	nombreArchivo = fichero;
	leerArchivo();
}

// Funcion que devuelve el siguiente caracter del buffer (-1 para EOF)
char siguienteEntrada()
{
	if (*delantero == EOF) {
		if (esFinDeFichero()) {
			return EOF; // Devolvemos fin de fichero
		}

		if (!flag) {
			cargarBuffer(++leyendoBuffer); // siguiente buffer
		} else {
			++leyendoBuffer; // avanzo de buffer sin cargarlo
			flag = 0; // quito el flag
		}
		//printf("\nCargo buffer %i\n", leyendoBuffer);
	}
	//printf("%c\n", *delantero);
	return *(delantero++); // retorno el contenido y lo avanzo
}

// Funcion que marca el inicio del actual lexema a leer
void marcarInicio()
{
	inicio = delantero;
}

// Funcion que retrasa el puntero delantero 1 posicion
void retroceder()
{
	if (leyendoBuffer == 0 && delantero == buffer1) {
		delantero = buffer2+N-1; // ultima posicion
		flag = 1;
	} else if (leyendoBuffer == 1 && delantero == buffer2) {
		delantero = buffer1+N-1; // ultima posicion
		flag = 1;
	} else {
		delantero--;
	}
}

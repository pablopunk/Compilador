//
// Fichero de implementacion del analizador sintactico
//

// Librerias de C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Librerias propias
#include "lexico.h"
#include "entrada.h"
#include "tabla_simbolos.h"
#include "definiciones.h"

int main(int argc, char** argv)
{
	int out=0;
	if (argc < 2) { // no hay argumentos de entrada
		printf("Sin argumentos...\n");
		return -1;
	}

	strcpy(nombreArchivo, argv[1]);
	if ( (out = leerArchivo()) ) {
		return out; // devuelvo el error que me devuelve la funcion
	}

	token* componente;

	// Iniciamos la tabla de simbolos
	inicializarTabla();
	// Inicializamos el lexico
	inicializarLexico();

	while ( (componente = siguienteComponenteLexico()) && (componente->numero != EOF) ) {
		if (componente->numero == ID && !busquedaTabla(componente->lexema)) { // Si es un ID lo metemos en la tabla
			insertarTabla(componente->lexema);
		}
		printf("%i| <%i>\t%s\n", componente->linea, componente->numero, componente->lexema);
	}

	//imprimirTabla();

	// Liberamos la tabla de simbolos
	liberarTabla();
	// Liberamos los componentes lexicos
	liberarLexico();

	return 0;
}

//
// Interfaz de la tabla de simbolos
//

#include "lexico.h"

// inicializar la tabla de simbolos y liberar
void inicializarTabla();
void liberarTabla();

// insertarar lexema en la tabla devuelve el numero (puede ser una palabra reservada o un ID)
int insertarTabla(lexema * l);

// buscar lexema en la tabla (1 si esta, 0 si no)
int busquedaTabla(lexema* l);

// Imprime la tabla de simbolos
void imprimirTabla();


//
// Interfaz del sistema de entrada
//


// Inicializar el sistema de entrada
void inicializarEntrada(char* fichero);

// Funcion de lectura, devuelve 0 en caso de que no haya errores
int leerArchivo();

// Funcion que devuelve el siguiente caracter del buffer (-1 para EOF)
char siguienteEntrada();

// Funcion que marca el inicio del actual lexema a leer
void marcarInicio();

// Funcion que retrasa el puntero delantero 1 posicion
void retroceder();

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <time.h>

/*
GNodo es una estructura que almacena 3 variables,
un void* dato que nos permite guardar informacion y
2 punteros a GNodo, ant y sig, que nos permiten referenciar al nodo anterior y siguiente respectivamente.
*/
typedef struct _GNodo {
	void* dato;
	struct _GNodo* ant;
	struct _GNodo* sig;
} GNodo ;

//Definimos a GList como un puntero a GNodo.
typedef GNodo* GList ;

/*
Definimos la estructura _Persona como los 3 datos que representaran a nuestras personas,
un char* Nombre, int Edad y char* Pais que almacenan la informacion indicada por sus nombres.
*/
typedef struct{
	char* Nombre;
	int Edad;
	char* Pais;
}_Persona;

/*
Definimos a Persona como el puntero a _Persona
para asi poder implementarla como un void* dato de un GNodo.
*/
typedef _Persona* Persona;

/*
Definimos Predicado como el puntero a una funcion que retorna toma un void* dato
y retorna un int representando si se cumple o no la condicion de la funcion.
*/
typedef int (*Predicado) (void* dato);

/*
Definimos Funcion como el puntero a una funcion que toma un void* dato
y retorna un void* representando el resultado de aplicar dicha funcion al dato recibido.
*/
typedef void* (*Funcion) (void* dato);

/*
Definimos Copia como el puntero a una funcion que recibe un void* dato
y retorna un void* que representa una copia fisica de memoria que contiene el dato recibido.
*/
typedef void* (*Copia) (void* dato);

/*
Definimos Destruir como el puntero a una funcion que recibe un void* dato
y elimina toda la informacion que almacena.
*/
typedef void (*Destruir) (void* dato);


// FUNCIONES DE LISTA

/*
Retorna la direccion de memoria donde se almacena la copia del dato pasado (Persona).
*/
void* copiar_persona(void* dato);

//Crea la lista vacia
GList crear_GList();

//Retorna un int determinando si la lista es vacia o no
int es_vacia(GList lista);

//Imprime en pantalla dato a dato la lista
void imprimir_GList(GList lista);

//Dados un Nombre, Edad y Pais, retorna una persona con esos datos
Persona crear_persona(char* Nombre, int Edad, char* Pais);

//Dado un dato, retorna un nodo nuevo con ese dato
GList crear_nodo(void* dato);

//Dados una lista y un dato, agrega un nodo a la lista con la informacion del dato
GList agregar_nodo(GList lista, void* dato);

/*
Dados un nombre de archivo, genera una lista, creando un nodo por cada linea del archivo,
donde los datos en el nodo seran el contenido de la linea
*/
GList generar_Glista_desde_archivo(char* nombre_archivo, GList lista);

//Dada una Persona, libera la memoria que ocupaba
void destriur_persona(void* dato);

/*
Dada una lista y una funcion destruir, libera la memoria de la lista
aplicando destruir en todos los datos de sus nodos, y luego liberando la memoria que ocupa el nodo.
*/
void gList_destruir(GList lista , Destruir d);

/*
Genera un archivo de nombre "nombre_archivo" a partir de la lista, donde cada linea del archivo
contendra los datos de cada nodo de la lista. El archivo no tiene una linea vacia al final.
*/
void GList_a_archivo(GList lista, char* nombre_archivo);

// FUNCIONES PARAMETRO PARA MAP Y FILTER

//Dada una Persona, retorna 1 (verdadero) si la persona es mayor de 50 anios
int mayores50(void* dato);

//Dada una Persona, retorna 1 (verdadero) si la persona es menor de 51 anios
int menores50(void* dato);

//Dada una Persona, retorna 1 (verdadero) si la persona es nacida en Peru
int peruanos(void* dato);

//Dada una Persona, retorna otra Persona identica pero con un año mas
void* aumentar_anio(void* dato);

//Dada una Persona, retorna otra Persona identica pero con su nombre cambiado a Messi
void* messi (void* dato);

// FUNCIONES MAP Y FILTER

/*
Retorna una copia de la lista original pasada como parametro, donde en cada nodo
se aplica la funcion f sobre el dato que contenga el nodo.
*/
GList map(GList lista_original, Funcion f, Copia c);

/*
Retorna una copia de la lista original pasada como parametro, donde solo los nodos que contengan datos
que cumplan el predicado p, seran copiados.
*/
GList filter(GList lista_original, Predicado p, Copia c);

/*
Esta funcion encapsula el comportamiento de la funcion map. Recibe como parametro una lista, un nombre de archivo, y una funcion f.
Mapea la funcion f sobre la lista pasada como argumento.
La lista mapeada se imprime en un archivo de salida que tendra de nombre el pasado como parametro.
*/
void aplica_map(GList lista, char* salida, Funcion f, Copia c, Destruir d);

/*
Esta funcion encapsula el comportamiento de la funcion filter. Recibe como parametro una lista, un nombre de archivo, y un predicado p.
Filtra la lista pasada como argumento, con el predicado p.
La lista filtrada se imprime en un archivo de salida que tendra de nombre el pasado como parametro.
*/
void aplica_filter(GList lista, char* salida, Predicado p, Copia c, Destruir d);

//MANEJO DE ARCHIVOS

//Reserva memoria para almacenar las palabras que seran leidas desde un archivo de ingreso.
void alojar_lista(char*** lista, int size);

/*
Carga_archivos guarda los datos en forma de string de las lineas del archivo
"nombre_archivo" en la lista "Lineas".
Ademas realoca la lista de no ser posible seguir agregando elementos.
Retorna la cantidad de lineas del archivo.
El archivo de ingreso debe contener una linea vacia al final del archivo, luego de las que contienen informacion.
Esto se debe a que asi fueron presentados los archivos en el enunciado.
*/
int carga_archivos(char* nombre_archivo, char*** Lineas, int size);

/*
generacion_archivo_personas recibe una lista de nombres, y paises.
Luego crea un archivo de salida con el nombre nombre_salida,
en el cual cada linea representara una persona, de lo forma:
Nombre, Edad, Pais. Estos datos son generados aleatoriamnete. El nombre y el pais de las listas
pasadas como parametros, y la edad un entero aleatorio entre 1 y 100.
El archivo generado tendra una cantidad de lineas igual al parametro cant_lineas ingresado
y no poseera una linea vacia al final del archivo.
*/
void generacion_archivo_personas(char* nombre_salida, char** paises, char** nombres, int cant_nombres, int cant_paises, int cantidad_lineas);

// Dado un puntero a punteros, libera la memoria de cada puntero, y del puntero que los referencia.
void liberar_lista(char** lista, int cantidad_lineas);
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <time.h>

/*
GNodo es una estructura que almacena 3 variables,
un void* dato que nos permite guardar informacion y
2 punteros a GNodo, ant y sig, que nos permiten referenciar al nodo anterior y siguiente respectivamente.
*/
typedef struct _GNodo {
	void* dato;
	struct _GNodo* ant;
	struct _GNodo* sig;
} GNodo ;

//Definimos a GList como un puntero a GNodo.
typedef GNodo* GList ;

/*
Definimos la estructura _Persona como los 3 datos que representaran a nuestras personas,
un char* Nombre, int Edad y char* Pais que almacenan la informacion indicada por sus nombres.
*/
typedef struct{
	char* Nombre;
	int Edad;
	char* Pais;
}_Persona;

/*
Definimos a Persona como el puntero a _Persona
para asi poder implementarla como un void* dato de un GNodo.
*/
typedef _Persona* Persona;

/*
Definimos Predicado como el puntero a una funcion que retorna toma un void* dato
y retorna un int representando si se cumple o no la condicion de la funcion.
*/
typedef int (*Predicado) (void* dato);

/*
Definimos Funcion como el puntero a una funcion que toma un void* dato
y retorna un void* representando el resultado de aplicar dicha funcion al dato recibido.
*/
typedef void* (*Funcion) (void* dato);

/*
Definimos Copia como el puntero a una funcion que recibe un void* dato
y retorna un void* que representa una copia fisica de memoria que contiene el dato recibido.
*/
typedef void* (*Copia) (void* dato);

/*
Definimos Destruir como el puntero a una funcion que recibe un void* dato
y elimina toda la informacion que almacena.
*/
typedef void (*Destruir) (void* dato);


// FUNCIONES DE LISTA

/*
Retorna la direccion de memoria donde se almacena la copia del dato pasado (Persona).
*/
void* copiar_persona(void* dato);

//Crea la lista vacia
GList crear_GList();

//Retorna un int determinando si la lista es vacia o no
int es_vacia(GList lista);

//Imprime en pantalla dato a dato la lista
void imprimir_GList(GList lista);

//Dados un Nombre, Edad y Pais, retorna una persona con esos datos
Persona crear_persona(char* Nombre, int Edad, char* Pais);

//Dado un dato, retorna un nodo nuevo con ese dato
GList crear_nodo(void* dato);

//Dados una lista y un dato, agrega un nodo a la lista con la informacion del dato
GList agregar_nodo(GList lista, void* dato);

/*
Dados un nombre de archivo, genera una lista, creando un nodo por cada linea del archivo,
donde los datos en el nodo seran el contenido de la linea
*/
GList generar_Glista_desde_archivo(char* nombre_archivo, GList lista);

//Dada una Persona, libera la memoria que ocupaba
void destriur_persona(void* dato);

/*
Dada una lista y una funcion destruir, libera la memoria de la lista
aplicando destruir en todos los datos de sus nodos, y luego liberando la memoria que ocupa el nodo.
*/
void gList_destruir(GList lista , Destruir d);

/*
Genera un archivo de nombre "nombre_archivo" a partir de la lista, donde cada linea del archivo
contendra los datos de cada nodo de la lista. El archivo no tiene una linea vacia al final.
*/
void GList_a_archivo(GList lista, char* nombre_archivo);

// FUNCIONES PARAMETRO PARA MAP Y FILTER

//Dada una Persona, retorna 1 (verdadero) si la persona es mayor de 50 anios
int mayores50(void* dato);

//Dada una Persona, retorna 1 (verdadero) si la persona es menor de 51 anios
int menores50(void* dato);

//Dada una Persona, retorna 1 (verdadero) si la persona es nacida en Peru
int peruanos(void* dato);

//Dada una Persona, retorna otra Persona identica pero con un año mas
void* aumentar_anio(void* dato);

//Dada una Persona, retorna otra Persona identica pero con su nombre cambiado a Messi
void* messi (void* dato);

// FUNCIONES MAP Y FILTER

/*
Retorna una copia de la lista original pasada como parametro, donde en cada nodo
se aplica la funcion f sobre el dato que contenga el nodo.
*/
GList map(GList lista_original, Funcion f, Copia c);

/*
Retorna una copia de la lista original pasada como parametro, donde solo los nodos que contengan datos
que cumplan el predicado p, seran copiados.
*/
GList filter(GList lista_original, Predicado p, Copia c);

/*
Esta funcion encapsula el comportamiento de la funcion map. Recibe como parametro una lista, un nombre de archivo, y una funcion f.
Mapea la funcion f sobre la lista pasada como argumento.
La lista mapeada se imprime en un archivo de salida que tendra de nombre el pasado como parametro.
*/
void aplica_map(GList lista, char* salida, Funcion f, Copia c, Destruir d);

/*
Esta funcion encapsula el comportamiento de la funcion filter. Recibe como parametro una lista, un nombre de archivo, y un predicado p.
Filtra la lista pasada como argumento, con el predicado p.
La lista filtrada se imprime en un archivo de salida que tendra de nombre el pasado como parametro.
*/
void aplica_filter(GList lista, char* salida, Predicado p, Copia c, Destruir d);

//MANEJO DE ARCHIVOS

//Reserva memoria para almacenar las palabras que seran leidas desde un archivo de ingreso.
void alojar_lista(char*** lista, int size);

/*
Carga_archivos guarda los datos en forma de string de las lineas del archivo
"nombre_archivo" en la lista "Lineas".
Ademas realoca la lista de no ser posible seguir agregando elementos.
Retorna la cantidad de lineas del archivo.
El archivo de ingreso debe contener una linea vacia al final del archivo, luego de las que contienen informacion.
Esto se debe a que asi fueron presentados los archivos en el enunciado.
*/
int carga_archivos(char* nombre_archivo, char*** Lineas, int size);

/*
generacion_archivo_personas recibe una lista de nombres, y paises.
Luego crea un archivo de salida con el nombre nombre_salida,
en el cual cada linea representara una persona, de lo forma:
Nombre, Edad, Pais. Estos datos son generados aleatoriamnete. El nombre y el pais de las listas
pasadas como parametros, y la edad un entero aleatorio entre 1 y 100.
El archivo generado tendra una cantidad de lineas igual al parametro cant_lineas ingresado
y no poseera una linea vacia al final del archivo.
*/
void generacion_archivo_personas(char* nombre_salida, char** paises, char** nombres, int cant_nombres, int cant_paises, int cantidad_lineas);

// Dado un puntero a punteros, libera la memoria de cada puntero, y del puntero que los referencia.
void liberar_lista(char** lista, int cantidad_lineas);

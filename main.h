#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <time.h>

typedef struct _GNodo {
	void* dato;
	struct _GNodo* sig ;
} GNodo ;

typedef GNodo* GList ;

typedef struct{
	char* Nombre;
	int Edad;
	char* Pais;
}_Persona;

typedef _Persona* Persona;

typedef int (*Predicado) (void* dato);

typedef void* (*Funcion) (void* dato);

typedef void* (*Copia) (void* dato);

typedef void (*Destruir) (void* dato);

// FUNCIONES PARAMETRO PARA MAP Y FILTER

//Retorna un int determinando si la Persona(dato) es mayor a 50 o no
int mayores50(void* dato);

//Retorna un int determinando si la Persona(dato) nacio en Peru o no
int peruanos(void* dato);

//Dada una Persona, retorna otra Persona identica pero con un año mas
void* aumentar_anio(void* dato);

//Dada una Persona, retorna otra Persona identica pero con todo el nombre en minuscula
void* nombre_minusculas (void* dato);

//Retorna una copia de la Persona(dato) en otro lugar de la memoria
//con el mismo dato que la original
void* copiar_persona(void* dato);

//Crea la lista vacia
GList crear_lista();

//Retorna un int determinando si la lista es vacia o no
int es_vacia(GList lista);

//Imprime en pantalla dato a dato la lista
void imprimir_lista(GList lista);

//Dados un Nombre, Edad y Pais, retorna una persona con esos datos
Persona crear_persona(char* Nombre, int Edad, char* Pais);

//Dado un dato, retorna un nodo nuevo con ese dato
GList crear_nodo(void* dato);

//Dados una lista y un dato, agrega un nodo a la lista con la informacion del dato
GList agregar_nodo(GList lista, void* dato);

//Dados un nombre_archivo y una lista, le agrega a la lista
//las lineas del archivo como datos de nodos
GList generar_lista_archivo(char* nombre_archivo, GList lista);

//Dada una Persona, libera la memoria que ocupaba
void destriur_persona(void* dato);

//Dada una lista y una funcion destruir, libera la memoria de la lista
//aplicando destruir en todos los datos de sus nodos
void gList_destruir (GList lista , Destruir d);

// FUNCIONES MAP Y FILTER

//Retorna una lista mapeada por la funcion f de la lista_original,
//copiandola con la funcion c
GList map(GList lista_original, Funcion f, Copia c);

//Retorna una lista filtrada por el predicado p de la lista_original,
//copiandola con la funcion c
GList filter(GList lista_original, Predicado p, Copia c);

//Genera un archivo de nombre "nombre_archivo" a partir de la lista
void GList_a_archivo(GList lista, char* nombre_archivo);


//MANEJO DE ARCHIVOS

/*
carga_archivos guarda los datos en forma de string de las lineas del archivo
"nombre_archivo" en la lista "Lineas"
*/
int carga_archivos(char* nombre_archivo, char Lineas[][100]);

void generacion_archivo(char* nombre_salida, char paises[][100], char nombres[][100], int cant_nombres, int cant_paises, int cantidad_lineas);


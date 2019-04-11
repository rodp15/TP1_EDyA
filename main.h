#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <time.h>

typedef struct _GNodo {
	void* dato;
	struct _GNodo* ant;
	struct _GNodo* sig;
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
int mayores50(void* dato);

int peruanos(void* dato);

void* aumentar_anio(void* dato);

void* nombre_minusculas (void* dato);

void* reverse (void* dato);

void* messi (void* dato);

void* copiar_persona(void* dato);

GList crear_lista();

int es_vacia(GList lista);

void imprimir_lista(GList lista);

Persona crear_persona(char* Nombre, int Edad, char* Pais);

GList crear_nodo(void* dato);

GList agregar_nodo(GList lista, void* dato);

GList generar_Glista_desde_archivo(char* nombre_archivo, GList lista);

void parser(char* linea_original, char* nombre, int* edad, char* pais);

void destriur_persona(void* dato);

void gList_destruir (GList lista , Destruir d);

// FUNCIONES MAP Y FILTER

GList map(GList lista_original, Funcion f, Copia c);

GList filter(GList lista_original, Predicado p, Copia c);

void GList_a_archivo(GList lista, char* nombre_archivo);

void aplica_map(GList lista, char* salida, Funcion f, Copia c, Destruir d);

void aplica_filter(GList lista, char* salida, Predicado p, Copia c, Destruir d);

//MANEJO DE ARCHIVOS

void alojar_lista(char*** lista, int size);

int carga_archivos(char* nombre_archivo, char*** Lineas, int size);

void generacion_archivo_personas(char* nombre_salida, char** paises, char** nombres, int cant_nombres, int cant_paises, int cantidad_lineas);

int string_length(char* texto);

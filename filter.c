#include "main.h"

//Retorna un int determinando si la Persona(dato) es mayor a 50 o no
int mayores50(void* dato){
	return (((Persona)dato)->Edad > 50);
}

//Retorna un int determinando si la Persona(dato) nacio en Peru o no
int peruanos(void* dato){
	return (strcmp(((Persona)dato)->Pais, "Perú") == 0);
}

/*
filter toma una lista (lista_original) y la recorre.
Verifica que los datos de cada nodo cumplan con un predicado (que viene dado por la funcion p) copiando los datos
con la funcion Copia (c) si cumplen el Predicado (p).
*/
GList filter(GList lista_original, Predicado p, Copia c){
	if(es_vacia(lista_original)) return lista_original;

	GList lista_filtrada = crear_lista(), referencia = lista_original;
	void* dato_copia;

	for(;lista_original->sig != referencia; lista_original = lista_original->sig){
		if(p(lista_original->dato)){
			dato_copia = c(lista_original->dato);
			lista_filtrada = agregar_nodo(lista_filtrada, dato_copia);
		}
	}
	if(p(lista_original->dato)){
		dato_copia = c(lista_original->dato);
		lista_filtrada = agregar_nodo(lista_filtrada, dato_copia);
	}
	return lista_filtrada;
}

void aplica_filter(GList lista, char* salida, Predicado p, Copia c, Destruir d){
	GList lista_filtrada = crear_lista();
	lista_filtrada = filter(lista, p, c);
	GList_a_archivo(lista_filtrada, salida);
	gList_destruir(lista_filtrada, d);
}

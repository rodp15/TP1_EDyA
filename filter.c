#include "main.h"

//Retorna un int determinando si la Persona(dato) es mayor a 50 o no
int mayores50(void* dato){
	return (((Persona)dato)->Edad > 50);
}

//Retorna un int determinando si la Persona(dato) nacio en Peru o no
int peruanos(void* dato){
	return (strcmp(((Persona)dato)->Pais, "Perú") == 0);
}

//Retorna una lista filtrada por el predicado p de la lista_original,
//copiandola con la funcion c
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
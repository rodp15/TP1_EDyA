#include "main.h"

int mayores50(void* dato){
	assert(dato && "La funcion mayores50 recibio NULL como parametro")
	return (((Persona)dato)->Edad > 50);
}

int menores50(void* dato){
	assert(dato && "La funcion menores50 recibio NULL como parametro")
	return (((Persona)dato)->Edad <= 50);
}


int peruanos(void* dato){
	assert(dato && "La funcion peruanos recibio NULL como parametro")
	return (strcmp(((Persona)dato)->Pais, "Perú") == 0);
}

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

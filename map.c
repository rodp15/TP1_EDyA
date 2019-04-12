#include "main.h"

void* aumentar_anio(void* dato){
	assert(dato && "La funcion aumentar_anio recibio NULL como parametro");
	((Persona)dato)->Edad++;
	return dato;
}

void* messi (void* dato){
	assert(dato && "La funcion messi recibio NULL como parametro");
	strcpy(((Persona)dato)->Nombre, "Messi");
	return dato;
}

GList map(GList lista_original, Funcion f, Copia c){
	if(es_vacia(lista_original)) return lista_original;

	GList lista_mapeada = crear_GList(), referencia = lista_original;
	void* dato_copia;

	for(;lista_original->sig != referencia; lista_original = lista_original->sig){
		dato_copia = f(c(lista_original->dato));
		lista_mapeada = agregar_nodo(lista_mapeada, dato_copia);
	}
	dato_copia = f(c(lista_original->dato));
	lista_mapeada = agregar_nodo(lista_mapeada, dato_copia);

	return lista_mapeada;
}

void aplica_map(GList lista, char* salida, Funcion f, Copia c, Destruir d){
	assert(f && c && d && "La funcion aplica_map recibio NULL como parametro de la direccion de memoria de alguna de las funciones que requiere");
	GList lista_mapeada = crear_GList();
	lista_mapeada = map(lista, f, c);
	GList_a_archivo(lista_mapeada, salida);
	gList_destruir(lista_mapeada, d);
}

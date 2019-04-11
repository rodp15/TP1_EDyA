#include "main.h"

//Dada una Persona, retorna otra Persona identica pero con un año mas
void* aumentar_anio(void* dato){
	((Persona)dato)->Edad++;
	return dato;
}

//Dada una Persona, retorna otra Persona identica pero con todo el nombre en minuscula
void* nombre_minusculas (void* dato) {
	char* nombre = ((Persona)dato)->Nombre;
	for (; *nombre; *nombre = tolower(*nombre), nombre++);
	return dato;
}

void* reverse (void* dato){
	char *nombre = ((Persona)dato)->Nombre, *reverso = (nombre + strlen(nombre) - 1), aux;
	for (int i = 0; i < ((strlen(nombre)-1)/2) ; i++){
		aux = *(nombre+i);
		*(nombre+i) = *(reverso-i);
		*(reverso-i) = aux;
	}
	return dato;
}

void* messi (void* dato){
	strcpy(((Persona)dato)->Nombre, "Messi");
	return dato;
}

//Retorna una lista mapeada por la funcion f de la lista_original,
//copiandola con la funcion c
GList map(GList lista_original, Funcion f, Copia c){
	if(es_vacia(lista_original)) return lista_original;

	GList lista_mapeada = crear_lista(), referencia = lista_original;
	void* dato_copia;
	
	for(;lista_original->sig != referencia; lista_original = lista_original->sig){
		dato_copia = f(c(lista_original->dato));
		lista_mapeada = agregar_nodo(lista_mapeada, dato_copia);
	}
	dato_copia = f(c(lista_original->dato));
	lista_mapeada = agregar_nodo(lista_mapeada, dato_copia);
	
	return lista_mapeada;
}

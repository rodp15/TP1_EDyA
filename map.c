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

//Retorna una lista mapeada por la funcion f de la lista_original,
//copiandola con la funcion c
GList map(GList lista_original, Funcion f, Copia c){
	GList lista_mapeada = crear_lista(), i;
	void* dato_copia;

	if(!es_vacia(lista_original)){
		dato_copia = f(c(lista_original->dato));
		lista_mapeada = crear_nodo(dato_copia);
		lista_original = lista_original->sig;
		i = lista_mapeada;
	}

	for(; !es_vacia(lista_original); lista_original = lista_original->sig, i = i->sig){
		dato_copia = f(c(lista_original->dato));
		i->sig = crear_nodo(dato_copia);
	}
	return lista_mapeada;
}

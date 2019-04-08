#include "main.h"

// FUNCIONES PARA CREACION DE LISTA


//Retorna una copia de la Persona(dato) en otro lugar de la memoria
//con el mismo dato que la original
void* copiar_persona(void* dato){
	Persona persona = (Persona)dato;

	if(!persona) return NULL;

	Persona persona_copiada = malloc(sizeof(_Persona));
	memcpy(persona_copiada, persona, sizeof(_Persona));
	int largo_nombre = (strlen(persona->Nombre) + 1),
		largo_pais =  (strlen(persona->Pais) + 1);

	persona_copiada->Nombre = malloc(sizeof(char) * largo_nombre);
	persona_copiada->Pais = malloc(sizeof(char) * largo_pais);
	memcpy( persona_copiada->Nombre , persona->Nombre , largo_nombre);
	memcpy( persona_copiada->Pais , persona->Pais , largo_pais);

	return persona_copiada;
}

//Crea la lista vacia
GList crear_lista(){
	return NULL;
}

//Retorna un int determinando si la lista es vacia o no
int es_vacia(GList lista){
	return lista == NULL;
}

//Imprime en pantalla dato a dato la lista
void imprimir_lista(GList lista){
	if (es_vacia(lista)) printf("Lista vacia\n");
	else{
		for(; !es_vacia(lista); lista = lista->sig){
			printf("%s, %d, %s\n", ((Persona)lista->dato)->Nombre, ((Persona)lista->dato)->Edad, ((Persona)lista->dato)->Pais);
		}
	}
}

//Dados un Nombre, Edad y Pais, retorna una persona con esos datos
Persona crear_persona(char* Nombre, int Edad, char* Pais){
	Persona nueva_persona = malloc(sizeof(_Persona));
	nueva_persona->Nombre = malloc(sizeof(char) * (strlen(Nombre) + 1));
	nueva_persona->Pais = malloc(sizeof(char) * (strlen(Pais) + 1));
	strcpy(nueva_persona->Nombre, Nombre);
	nueva_persona->Edad = Edad;
	strcpy(nueva_persona->Pais, Pais);

	return nueva_persona;
}

//Dado un dato, retorna un nodo nuevo con ese dato
GList crear_nodo(void* dato){
	GList nuevo_nodo = malloc(sizeof(GNodo));
	nuevo_nodo->dato = dato;
	nuevo_nodo->sig = NULL;
	return nuevo_nodo;
}

//Dados una lista y un dato, agrega un nodo a la lista con la informacion del dato
GList agregar_nodo(GList lista, void* dato){
	GList nuevo_nodo = crear_nodo(dato);

	if(es_vacia(lista)) return nuevo_nodo;

	GList i = lista;
	for(; !es_vacia(i->sig) ; i = i->sig);
	i->sig = nuevo_nodo;
	return lista;
}

//Dados un nombre_archivo y una lista, le agrega a la lista
//las lineas del archivo como datos de nodos
GList generar_lista_archivo(char* nombre_archivo, GList lista){
	//VALIDACIONES SOBRE ARCHIVO
	FILE *archivo = fopen(nombre_archivo,"r");
	char buff_nom[100], buff_pais[100];
	int buff_edad;
	for(;!feof(archivo);){
		fscanf(archivo, " %[^,], %d, %[^\n]", buff_nom, &buff_edad, buff_pais);
		lista = agregar_nodo(lista, crear_persona(buff_nom, buff_edad, buff_pais));
	}
	fclose(archivo);
	return lista;
}

//Dada una Persona, libera la memoria que ocupaba
void destriur_persona(void* dato){
	Persona persona = (Persona)dato;
	free(persona->Nombre);
	free(persona->Pais);
	//free(persona);
}

//Dada una lista y una funcion destruir, libera la memoria de la lista
//aplicando destruir en todos los datos de sus nodos
void gList_destruir (GList lista , Destruir d){
	GList i = lista, aux;
	for(; !es_vacia(i) ; i = aux){
		d(i->dato);
		aux = i->sig;
		free(i);
	}
}


//Genera un archivo de nombre "nombre_archivo" a partir de la lista
void GList_a_archivo(GList lista, char* nombre_archivo) {
	FILE* archivo = fopen(nombre_archivo, "w");

	for (; !es_vacia(lista); lista = lista->sig){
		fprintf(archivo, "%s, ", ((Persona)lista->dato)->Nombre);
		fprintf(archivo, "%d, ", ((Persona)lista->dato)->Edad);
		fprintf(archivo, "%s\n", ((Persona)lista->dato)->Pais);
	}
	fclose(archivo);
}

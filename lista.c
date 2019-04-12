#include "main.h"

void* copiar_persona(void* dato){
	//Casteamos el dato a una Persona para manejarlo mas facil.
	Persona persona = (Persona)dato;

	//Si la persona es NULL, retornamos NULL.
	if(!persona) return NULL;

	//Reservamos memoria y copiamos la informacion de la persona original en persona_copiada.
	Persona persona_copiada = malloc(sizeof(_Persona));
	memcpy(persona_copiada, persona, sizeof(_Persona));

	int largo_nombre = (strlen(persona->Nombre) + 1),
		largo_pais =  (strlen(persona->Pais) + 1);

	//Reservamos memoria y copiamos la informacion del Nombre, Edad y Pais.
	persona_copiada->Nombre = malloc(sizeof(char) * largo_nombre);
	persona_copiada->Pais = malloc(sizeof(char) * largo_pais);
	memcpy( persona_copiada->Nombre , persona->Nombre , largo_nombre);
	memcpy( persona_copiada->Pais , persona->Pais , largo_pais);

	return persona_copiada;
}

GList crear_lista(){
	return NULL;
}

int es_vacia(GList lista){
	return lista == NULL;
}

void imprimir_lista(GList lista){
	if (es_vacia(lista)) printf("Lista vacia\n");

	else{
		GList referencia = lista;
		for(;lista->sig != referencia; lista = lista->sig){
			printf("%s, %d, %s\n", ((Persona)lista->dato)->Nombre, ((Persona)lista->dato)->Edad, ((Persona)lista->dato)->Pais);
		}
		//Imprimimos el ultimo elemento de la lista.
		printf("%s, %d, %s\n", ((Persona)lista->dato)->Nombre, ((Persona)lista->dato)->Edad, ((Persona)lista->dato)->Pais);
	}
}

Persona crear_persona(char* Nombre, int Edad, char* Pais){
	//Reservamos memoria para la nueva_persona y su informacion.
	Persona nueva_persona = malloc(sizeof(_Persona));
	nueva_persona->Nombre = malloc(sizeof(char) * (strlen(Nombre) + 1));
	nueva_persona->Pais = malloc(sizeof(char) * (strlen(Pais) + 1));
	//Guardamos la informacion en la nueva_persona.
	strcpy(nueva_persona->Nombre, Nombre);
	nueva_persona->Edad = Edad;
	strcpy(nueva_persona->Pais, Pais);

	return nueva_persona;
}

GList crear_nodo(void* dato){
	GList nuevo_nodo = malloc(sizeof(GNodo));

	nuevo_nodo->dato = dato;
	nuevo_nodo->ant = nuevo_nodo;
	nuevo_nodo->sig = nuevo_nodo;

	return nuevo_nodo;
}

GList agregar_nodo(GList lista, void* dato){
	//Creamos el nuevo_nodo que agregaremos al final de la lista.
	GList nuevo_nodo = crear_nodo(dato);

	if(es_vacia(lista)) return nuevo_nodo;

	//Reasingamos los punteros de la lista y del nuevo_nodo
	//para que quede el nuevo_nodo como el ultimo de la lista.
	nuevo_nodo->sig = lista;
	nuevo_nodo->ant = lista->ant;
	lista->ant->sig = nuevo_nodo;
	lista->ant = nuevo_nodo;

	return lista;
}

GList generar_Glista_desde_archivo(char* nombre_archivo, GList lista){
	FILE *archivo = fopen(nombre_archivo,"r");

	if(!archivo) return lista;

	char buff_nom[100], buff_pais[100];
	int buff_edad;

	//Recorremos el archivo leyendo las lineas hasta el EOF.
	//Parseamos las lineas para guardar solo la informacion necesaria
	//y luego agregamos un nodo a la lista con la informacion leida.
	while(EOF != fscanf(archivo, " %[^,], %d, %[^\r\n]\r\n", buff_nom, &buff_edad, buff_pais)){
		lista = agregar_nodo(lista, crear_persona(buff_nom, buff_edad, buff_pais));
	}

	fclose(archivo);

	return lista;
}

void destriur_persona(void* dato){
	Persona persona = (Persona)dato;
	free(persona->Nombre);
	free(persona->Pais);
	free(persona);
}

void gList_destruir (GList lista , Destruir d){
	if(es_vacia(lista)) return;

	GList i = lista, aux;

	for(; i->sig != lista; i = aux){
		d(i->dato);
		aux = i->sig;
		free(i);
	}
	d(i->dato);
	free(i);
}

void GList_a_archivo(GList lista, char* nombre_archivo) {
	FILE* archivo = fopen(nombre_archivo, "w");
	GList referencia = lista;

	if(!es_vacia(lista)){
		for (;lista->sig != referencia; lista = lista->sig){
			fprintf(archivo, "%s, ", ((Persona)lista->dato)->Nombre);
			fprintf(archivo, "%d, ", ((Persona)lista->dato)->Edad);
			fprintf(archivo, "%s\n", ((Persona)lista->dato)->Pais);
		}
		fprintf(archivo, "%s, ", ((Persona)lista->dato)->Nombre);
		fprintf(archivo, "%d, ", ((Persona)lista->dato)->Edad);
		fprintf(archivo, "%s", ((Persona)lista->dato)->Pais);
	}
	fclose(archivo);
}

#include "main.h"

void alojar_lista(char*** lista, int size){
  (*lista) = malloc(sizeof(char*) * size);
}

int carga_archivos(char* nombre_archivo, char*** Lineas, int size){
	FILE* archivo = fopen(nombre_archivo, "r");
  //Corroboramos la existencia del archivo.
  assert("No existe el archivo ingresado de lectura" && archivo);

  int cant_lineas = 0, largo;
  char aux[100];

  //Recorremos el archivo hasta el EOF guardando en aux las lineas parseadas.
	while(EOF != fscanf(archivo, "%[^\r\n]\r\n", aux)){

    largo = strlen(aux);
    //Guardamos el lugar para la palabra.
    (*Lineas)[cant_lineas] = malloc(sizeof(char) * (largo + 1));
    aux[largo] = '\0';

    //Guardamos la informacion de aux en nuestra lista.
    strcpy((*Lineas)[cant_lineas], aux);

		cant_lineas++;

    //Si la cantidad de lineas coincide con el tamanio de la lista,
    //realocamos la lista con el doble de espacio.
    if (cant_lineas == size){
      size *= 2;
      (*Lineas) = realloc((*Lineas), sizeof(char*) * size);
      assert(*Lineas);
    }
	}

	fclose(archivo);

	return cant_lineas;
}

void generacion_archivo_personas(char* nombre_salida, char** paises, char** nombres, int cant_nombres, int cant_paises, int cantidad_lineas){
	FILE* archivo = fopen(nombre_salida, "w");
	char buff_nombre[100], buff_pais[100];
	int r;

	for(int i = 0; i < cantidad_lineas; i++){
		r = (rand() % cant_nombres);
		strcpy(buff_nombre, nombres[r]);
		r = (rand() % cant_paises);
		strcpy(buff_pais, paises[r]);
		r = (rand() % 100) + 1;
		fprintf(archivo, "%s, %d, %s", buff_nombre, r, buff_pais);
		fprintf(archivo, "\n");
	}

	fclose(archivo);
}

void liberar_lista(char** lista, int cant_lineas){
  for(int i = 0; i < cant_lineas; free(lista[i]), i++);
  free(lista);
}

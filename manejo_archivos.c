#include "main.h"

void alojar_lista(char*** lista, int size){
  (*lista) = malloc(sizeof(char*) * size);
}

int carga_archivos(char* nombre_archivo, char*** Lineas, int size){
	FILE* archivo = fopen(nombre_archivo, "r");
	int cant_lineas = 0, largo;
	char c, aux[100];

	//corroboramos la existencia del archivo
	if (archivo == NULL) return 0;

	//verificamos si esta vacio
	c = fgetc(archivo);
	if (c == EOF) return 0;
	ungetc(c, archivo);

	while(EOF != fscanf(archivo, "%[^\r\n]\r\n", aux)){

    largo = strlen(aux);
    (*Lineas)[cant_lineas] = malloc(sizeof(char) * (largo + 1));
    aux[largo] = '\0';

    strcpy((*Lineas)[cant_lineas], aux);
		cant_lineas++;

    //Si la cantidad de lineas coincide con el tamaño de la lista,
    //realocamos la lista con el doble de espacio
    if (cant_lineas == size){
      size *= 2;
      (*Lineas) = realloc((*Lineas), sizeof(char*) * size);
      assert(*Lineas);
    }
	}

	fclose(archivo);
	return --cant_lineas;
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
		if(i != (cantidad_lineas-1)) fprintf(archivo, "\n");
	}

	fclose(archivo);
}

void liberar_lista(char** lista, int cant_lineas){
  for(int i = 0; i < cant_lineas; free(lista[i]), i++);
  free(lista);
}

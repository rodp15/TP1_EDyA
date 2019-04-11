#include "main.h"

//string_length mide la longitud del texto hasta que encuentre un \r, \n o \0
int string_length(char* texto){
    int i;
    for (i = 0; texto[i] != '\n' && texto[i] != '\r' && texto[i] != '\0'; i++);
    return i;
}

//Aloja en memoria el contenido de lista para punteros con el tamaño size
void alojar_lista(char*** lista, int size){
  (*lista) = malloc(sizeof(char*) * size);
}

/*
Carga_archivos guarda los datos en forma de string de las lineas del archivo
"nombre_archivo" en la lista "Lineas".
Ademas realoca la lista de no ser posible seguir agregando elementos.
Retorna la cantidad de lineas del archivo.
El archivo de ingreso debe contener una linea vacia al final del archivo, luego de las que contienen informacion.
Esto se debe a que asi fueron presentados los archivos en el enunciado.
*/
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

	while(!feof(archivo)){
		fgets(aux, 100, archivo);
    largo = string_length(aux);
    (*Lineas)[cant_lineas] = malloc(sizeof(char) * (largo + 1) * 2);
    strcpy((*Lineas)[cant_lineas], aux);
		(*Lineas)[cant_lineas][largo] = '\0';

    printf("%d %s\n", cant_lineas, (*Lineas)[cant_lineas]);

		cant_lineas++;

    //Si la cantidad de lineas coincide con el tamaño de la lista,
    //realocamos la lista con el doble de espacio
    if (cant_lineas == size){
      printf("%d\n", cant_lineas);
      size *= 2;
      (*Lineas) = realloc((*Lineas), sizeof(char*) * size);
      assert(*Lineas);
      //printf("realloc\n");
    }
	}

	fclose(archivo);
	return --cant_lineas;
}

// NO tiene una linea en blanco al final del archivo
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

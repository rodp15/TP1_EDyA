#include "main.h"


int string_length(char* texto){
    int i;
    for (i = 0; texto[i] != '\n' && texto[i] != '\r'; i++);
    return i;
}

/*
carga_archivos guarda los datos en forma de string de las lineas del archivo
"nombre_archivo" en la lista "Lineas"
*/
int carga_archivos(char* nombre_archivo, char Lineas[][100]){
	FILE* archivo = fopen(nombre_archivo,"r");
	int cant_lineas = 0, largo;
	char c;

	//corroboramos la existencia del archivo
	if (archivo == NULL) return 0;

	//verificamos si esta vacio
	c = fgetc(archivo);
	if (c == EOF) return 0;
	ungetc(c, archivo);

	while(!feof(archivo)){
		fgets(Lineas[cant_lineas], 100, archivo);
		largo = string_length(Lineas[cant_lineas]);
		Lineas[cant_lineas][largo]='\0';
		cant_lineas++;
	}

	fclose(archivo);
	return --cant_lineas;
}

void generacion_archivo(char* nombre_salida, char paises[][100], char nombres[][100], int cant_nombres, int cant_paises, int cantidad_lineas){
	FILE* archivo=fopen(nombre_salida, "w");
	char buff_nombre[100], buff_pais[100];
	int i, r;
	for(i = 0; i < cantidad_lineas; i++){
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


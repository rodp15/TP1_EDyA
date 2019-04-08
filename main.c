#include "main.h"

int main(){
	srand(time(NULL));
	char Nombres[4000][100], Paises[4000][100];
	int cant_nombres=carga_archivos("nombres.txt",Nombres), cant_paises=carga_archivos("paises.txt", Paises);

	if (cant_nombres == 0 || cant_paises == 0) {
		printf("Error al leer el archivo. El mismo no existe o esta vacio\n");
		return 0;
	}
	generacion_archivo("salida.txt", Paises, Nombres, cant_nombres, cant_paises, 2801);
		
	GList lista_personas = crear_lista();
	lista_personas = generar_lista_archivo("salida.txt", lista_personas);

	//imprimir_lista(lista_personas);

	lista_personas = filter(lista_personas, &mayores50, &copiar_persona);
	//imprimir_lista(lista_filter);

	lista_personas = map(lista_personas, &nombre_minusculas, &copiar_persona);
	//imprimir_lista(lista_personas);

	GList_a_archivo(lista_personas, "glist.txt");

	return 0;
}

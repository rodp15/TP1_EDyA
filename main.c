#include "main.h"

int main() {
	srand(time(NULL));
	//Nombres es una lista de todos los nombres del archivo de entrada de nombres.
	//Paises es una lista de todos los paises del archivo de entrada de paises.
	char **Nombres, **Paises;
	//size es el tamanio inicial de Nombres y Paises.
	int size = 2048;

	//Reservamos memoria para Nombres y Paises
	alojar_lista(&Nombres, size);
	alojar_lista(&Paises, size);

	//Conseguimos la cant_nombres y cant_paises y ademas
	//cargamos los nombres y paises de la entrada a nuestras listas.
	int cant_nombres = carga_archivos("nombres.txt", &Nombres, size);
	int cant_paises = carga_archivos("paises.txt", &Paises, size);

	assert(cant_nombres && cant_paises &&
		"Error al leer los archivos de nombres y paises. Alguno esta vacio\n");

	generacion_archivo_personas("salida.txt", Paises, Nombres, cant_nombres, cant_paises, 10000);

	liberar_lista(Nombres, cant_nombres);
	liberar_lista(Paises, cant_paises);

	GList lista_personas = crear_GList();
	lista_personas = generar_Glista_desde_archivo("salida.txt", lista_personas);

	aplica_map(lista_personas, "primer_map.txt", &aumentar_anio, &copiar_persona, &destriur_persona);
	aplica_map(lista_personas, "segundo_map.txt", &messi, &copiar_persona, &destriur_persona);

	aplica_filter(lista_personas, "primer_filter.txt", &peruanos, &copiar_persona, &destriur_persona);
	aplica_filter(lista_personas, "segundo_filter.txt", &mayores50, &copiar_persona, &destriur_persona);
	aplica_filter(lista_personas, "tercer_filter.txt", &menores50, &copiar_persona, &destriur_persona);

	gList_destruir(lista_personas, &destriur_persona);

	return 0;
}

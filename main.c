#include "main.h"

int main(){
	srand(time(NULL));
	char Nombres[4000][100], Paises[4000][100];
	int cant_nombres=carga_archivos("nombres.txt",Nombres), cant_paises=carga_archivos("paises.txt", Paises);

	if (cant_nombres == 0 || cant_paises == 0) {
		printf("Error al leer los archivos de nombres y paises. Alguno o ambos no existe o esta vacio\n");
		return 0;
	}
	
	generacion_archivo_personas("salida.txt", Paises, Nombres, cant_nombres, cant_paises, 2000);
		
	GList lista_personas = crear_lista();
	lista_personas = generar_Glista_desde_archivo("salida.txt", lista_personas);
	aplica_map(lista_personas, "primer_map.txt", &aumentar_anio, &copiar_persona, &destriur_persona);
	aplica_map(lista_personas, "segundo_map.txt", &messi, &copiar_persona, &destriur_persona);
	aplica_filter(lista_personas, "primer_filter.txt", &peruanos, &copiar_persona, &destriur_persona);
	aplica_filter(lista_personas, "segundo_filter.txt", &mayores50, &copiar_persona, &destriur_persona);

	return 0;
}

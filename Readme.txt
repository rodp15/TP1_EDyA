En este archivo comprimido se encuentran:
- 5 archivos .c con el codigo del programa.
- Un archivo .h (Header) con las declaraciones de todo lo necesario para el funcionamiento del programa (Estrcturas, tipos de dato, funciones). En el mismo se encuentra la documentacion de las mismas.
- Los archivos nombres.txt y paises.txt, cuyos nombres no deben ser modificados para la correcta ejecucion del programa.
- Dos archivos ejecutables (CompilarLinux.sh y CompilarWindows.bat) con el comando de compilacion utilizado. el mismo es 
gcc -std=c99 -Wall -Werror -o ejectuable main.c map.c lista.c manejo_archivos.c filter.c.

Ademas:
- Todos los archivos de texto, contienen una linea en blanco al final (linea vacia con un salto de linea). Esto es asi para estandarizar todos los archivos, y ya que los dos entregados por la catedra (nombres.txt y paises.txt) tenian este formato.
- Todos los archivos estan indentados con nuestras propias convenciones, con las cuales hemos sido consistentes.
- En el flujo del programa se encuentran asserts para chequear condiciones que llevarian a una interrupcion de la ejecucion.
- El archivo generado en la primer parte del enunciado posee el nombre de "salida.txt", el cual no debe ser modificado para la correcta ejecucion del programa. El mismo contiene 10000 lineas, que representan esa misma cantidad de personas que seran agregadas a la lista en la segunda parte del codigo.
- La implementacion de lista general es una lista circular doblemente enlazada. Esto es para obtener un rapido acceso al primer y ultimo elemento de la lista, lo cual resulta necesario para implementar eficientemente el agregado de elementos (nodos) a la lista. Esto es porque si insertaramos los elementos siempre al inicio de la lista, la misma se invertiria con cada ejecucion de un map/filter.
- Para resolver la problematica presentada con los caracteres especiales, tomamos la desicion de trabajarlos como una concatenacion de caracteres normales(es decir, todo caracter que se encuentre en el input, estara en el output del programa). 
Tomamos la precaucion de no modificar estos caracteres, ni invertir su orden, para no romper su codificacion.
Tomando esta desicion, los caracteres funcionan correctamente y no se "rompen" en el output. Tener en cuenta que las funciones utilizadas para mapear la lista nunca modifican los caracteres de los strings que son parte de los datos, sino que a lo sumo los reemplazan completamente.
- Hay 2 ejecuciones de la funcion map, las cuales generan los archivos de salida "primer_map.txt" y "segundo_map.txt".
Hay 3 ejecuciones de la funcion filter, las cuales generan los archivos "primer_filter.txt", "segundo_filter.txt" y "tercer_filter.txt"

El trabajo presentado fue realizado por Agustin Diaz y Rodrigo Peralta.
 
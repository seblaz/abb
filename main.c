#include "testing.h"
#include <stdlib.h>
#include <stdio.h>

/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

void pruebas_arbol();
void pruebas_volumen_arbol(size_t);
void pruebas_nodo();

int main(int argc, char *argv[])
{
    if (argc > 1) {
        // Asumimos que nos están pidiendo pruebas de volumen.
        long largo = strtol(argv[1], NULL, 10);
        pruebas_volumen_arbol((size_t) largo);
        return 0;
    }

    pruebas_nodo();
    pruebas_arbol();

    return failure_count() > 0;
}

// int main(int argc, char *argv[]){
//   return 0;
// }

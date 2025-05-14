#include <stdlib.h>
#include "hilos.h"

void *contarNoCero(void *arg) {
    DatosHilos *datos = (DatosHilos *)arg;
    int contador = 0;
    for (int i = datos->filaInicial; i < datos->filaFinal; i++) {
        for (int j = 0; j < datos->columnas; j++) {
            if (datos->matriz[i][j] != 0) {
                contador++;
            }
        }
    }
    datos->contadorNoCeros = contador;
    return NULL;
}

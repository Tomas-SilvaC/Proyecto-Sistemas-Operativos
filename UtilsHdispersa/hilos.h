#include <stdio.h>
#include <stdlib.h>

#ifndef HILOS_H
#define HILOS_H

typedef struct {
    int filaInicial;
    int filaFinal;
    int columnas;
    int **matriz;
    int contadorNoCeros;
} DatosHilos;

void *contarNoCero(void *arg);

#endif

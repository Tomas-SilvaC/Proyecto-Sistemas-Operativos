/**************************************************************
                Pontificia Universidad Javeriana
        Autores: Gabriel Jaramillo, Juan Pabón, Tomas Silva y Felipe Rodrpiguez
        Fecha: Mayo 2025
        Materia: Sistemas Operativos
        Tema: Proyecto Final
        Fichero: hilos.h
        Descripción: 
            
****************************************************************/

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

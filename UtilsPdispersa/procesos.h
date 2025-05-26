/**************************************************************
                Pontificia Universidad Javeriana
        Autores: Gabriel Jaramillo, Juan Pabón, Tomas Silva y Felipe Rodrpiguez
        Fecha: Mayo 2025
        Materia: Sistemas Operativos
        Tema: Proyecto Final
        Fichero: procesos.h
        Descripción: 
            Este fichero
****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef PROCESOS_H
#define PROCESOS_H

#define ARCHIVO_PATRON "sparse_temp_%d.txt"
typedef struct {
    int filaInicial;
    int filaFinal;
    int columnas;
    int **matriz;
    int contadorNoCeros;
} DatosProcesos;

int contarNoCero(DatosProcesos arg);
void funcProceso(DatosProcesos arg);

#endif

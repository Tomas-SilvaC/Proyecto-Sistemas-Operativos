/**************************************************************
                Pontificia Universidad Javeriana
        Autores: Gabriel Jaramillo, Juan Pabón, Tomas Silva y Felipe Rodrpiguez
        Fecha: Mayo 2025
        Materia: Sistemas Operativos
        Tema: Proyecto Final
        Fichero: matriz.h
        Descripción: 
            Este fichero 
****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#ifndef MATRIZ_H
#define MATRIZ_H

int **crearMatriz(int filas, int columnas);
void liberarMatriz(int **matriz, int filas);
int cargarMatriz(char *nombreArchivo, int **matriz, int filas, int columnas);

#endif

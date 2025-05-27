/**************************************************************
                Pontificia Universidad Javeriana
        Autores: Gabriel Jaramillo, Juan Pabón, Tomas Silva y Felipe Rodrpiguez
        Fecha: Mayo 2025
        Materia: Sistemas Operativos
        Tema: Proyecto Final
        Fichero: matriz.h
        Descripción: 
             Interfaz para el manejo de matrices dinámicas:
            - Declaración de funciones para creación/liberación de matrices
            - Definición de operaciones de carga desde archivos
****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#ifndef MATRIZ_H
#define MATRIZ_H

int **crearMatriz(int filas, int columnas); // Función para crear una matriz dinámica de enteros de tamaño filas x columnas
void liberarMatriz(int **matriz, int filas); // Función para liberar la memoria ocupada por una matriz previamente creada
int cargarMatriz(char *nombreArchivo, int **matriz, int filas, int columnas); // Función para cargar los valores de una matriz desde un archivo de texto

#endif

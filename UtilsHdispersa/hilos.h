/**************************************************************
                Pontificia Universidad Javeriana
        Autores: Gabriel Jaramillo, Juan Pabón, Tomas Silva y Felipe Rodrpiguez
        Fecha: Mayo 2025
        Materia: Sistemas Operativos
        Tema: Proyecto Final
        Fichero: hilos.h
        Descripción: 
            Interfaz para el manejo de hilos en el proyecto:
            - Estructura de datos para parámetros de hilos
            - Declaración de función principal para conteo de no ceros
****************************************************************/

#include <stdio.h>
#include <stdlib.h>

#ifndef HILOS_H
#define HILOS_H

typedef struct {
    int filaInicial; // Índice de la primera fila a procesar
    int filaFinal; // Índice de la última fila a procesar
    int columnas; // Número de columnas en la matriz
    int **matriz; // Puntero a la matriz compartida
    int contadorNoCeros;  // Resultado parcial del conteo
} DatosHilos;

void *contarNoCero(void *arg); // Función ejecutada por cada hilo para contar elementos no cero

#endif

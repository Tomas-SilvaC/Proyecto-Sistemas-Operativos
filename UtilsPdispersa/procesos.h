/**************************************************************
                Pontificia Universidad Javeriana
        Autores: Gabriel Jaramillo, Juan Pabón, Tomas Silva y Felipe Rodrpiguez
        Fecha: Mayo 2025
        Materia: Sistemas Operativos
        Tema: Proyecto Final
        Fichero: procesos.h
        Descripción: 
            Interfaz para el manejo de procesos en el proyecto:
            - Estructura de datos para parámetros de procesos
            - Declaración de función principal para conteo de no ceros
****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef PROCESOS_H
#define PROCESOS_H

// Define una estructura de archivo para la comunicación entre procesos
#define ARCHIVO_PATRON "sparse_temp_%d.txt" 
typedef struct {
    int filaInicial; // Índice de la primera fila a procesar
    int filaFinal; // Índice de la última fila
    int columnas; // Número de columnas en la matriz
    int **matriz; // Apuntador a la matriz compartida
    int contadorNoCeros; // Resultado parcial del conteo
} DatosProcesos;

int contarNoCero(DatosProcesos arg); // Cuenta elementos no cero en un segmento de matriz
void funcProceso(DatosProcesos arg); // Función principal ejecutada por cada proceso hijo

#endif

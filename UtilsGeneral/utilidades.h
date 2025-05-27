/**************************************************************
                Pontificia Universidad Javeriana
        Autores: Gabriel Jaramillo, Juan Pabón, Tomas Silva y Felipe Rodrpiguez
        Fecha: Mayo 2025
        Materia: Sistemas Operativos
        Tema: Proyecto Final
        Fichero: utilidades.h
        Descripción: 
            Interfaz para el procesamiento de argumentos de línea de comandos:
            - Declaración de función para validación de parámetros de entrada 
****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef UTILIDADES_H
#define UTILIDADES_H

int procesarArgumentos(int argc, char *argv[], int *filas, int *columnas, char **archivo, int *hilos, int *porcentaje); // Procesa y valida los argumentos de línea de comandos

#endif

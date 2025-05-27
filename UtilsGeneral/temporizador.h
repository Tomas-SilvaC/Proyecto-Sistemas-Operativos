/**************************************************************
                Pontificia Universidad Javeriana
        Autores: Gabriel Jaramillo, Juan Pabón, Tomas Silva y Felipe Rodrpiguez
        Fecha: Mayo 2025
        Materia: Sistemas Operativos
        Tema: Proyecto Final
        Fichero: temporizador.h
        Descripción: 
            Interfaz para medición precisa de tiempos de ejecución:
            - Declaración de funciones para control del temporizador
            - Definición de estructura para almacenamiento de tiempos 
****************************************************************/

#ifndef TEMPORIZADOR_H
#define TEMPORIZADOR_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>

// Variables globales compartidas
extern struct timeval tiempoInicio, tiempoFin;

void iniciarTemporizador(); // Inicia el temporizador guardando el tiempo actual
double detenerTemporizador(); // Detiene el temporizador y calcula el tiempo transcurrido

#endif

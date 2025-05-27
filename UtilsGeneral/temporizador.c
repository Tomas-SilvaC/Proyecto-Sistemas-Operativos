/**************************************************************
                Pontificia Universidad Javeriana
        Autores: Gabriel Jaramillo, Juan Pabón, Tomas Silva y Felipe Rodrpiguez
        Fecha: Mayo 2025
        Materia: Sistemas Operativos
        Tema: Proyecto Final
        Fichero: temporizador.c
        Descripción: 
            Implementación de funciones para medición precisa de tiempos:
            - Uso de gettimeofday() para máxima precisión (microsegundos)
            - Cálculo del tiempo transcurrido entre inicio y fin 
****************************************************************/

#include "temporizador.h"

// Variables globales para almacenar los tiempos de inicio y fin
struct timeval tiempoInicio, tiempoFin;

/* Función que inicia el temporizador guardando
   el tiempo actual */
void iniciarTemporizador() {
    gettimeofday(&tiempoInicio, (void *)0);
}

/* Función que detiene el temporizador y calcula
   el tiempo transcurrido */
double detenerTemporizador() {
    // Obtiene el tiempo actual de finalización
    gettimeofday(&tiempoFin, (void *)0);

    // Calcula la diferencia en microsegundos
    tiempoFin.tv_usec -= tiempoInicio.tv_usec;
    tiempoFin.tv_sec -= tiempoInicio.tv_sec;

    // Convierte a microsegundos y muestra el resultado
    double tiempo = (double)(tiempoFin.tv_sec*1000000 + tiempoFin.tv_usec);
    printf("%f\n", tiempo);
    return tiempo;
}

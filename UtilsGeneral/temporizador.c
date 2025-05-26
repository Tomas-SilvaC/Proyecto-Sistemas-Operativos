/**************************************************************
                Pontificia Universidad Javeriana
        Autores: Gabriel Jaramillo, Juan Pabón, Tomas Silva y Felipe Rodrpiguez
        Fecha: Mayo 2025
        Materia: Sistemas Operativos
        Tema: Proyecto Final
        Fichero: temporizador.c
        Descripción: 
            Este fichero 
****************************************************************/

#include "temporizador.h"

struct timeval tiempoInicio, tiempoFin;

void iniciarTemporizador() {
    gettimeofday(&tiempoInicio, (void *)0);
}

double detenerTemporizador() {
    gettimeofday(&tiempoFin, (void *)0);
    tiempoFin.tv_usec -= tiempoInicio.tv_usec;
    tiempoFin.tv_sec -= tiempoInicio.tv_sec;
    double tiempo = (double)(tiempoFin.tv_sec*1000000 + tiempoFin.tv_usec);
    printf("%f\n", tiempo);
    return tiempo;
}

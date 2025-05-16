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
    printf("%9.0f \n", tiempo);
    return tiempo;
}
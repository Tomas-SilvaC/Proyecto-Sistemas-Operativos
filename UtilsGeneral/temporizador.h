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

extern struct timeval tiempoInicio, tiempoFin;

void iniciarTemporizador();
void detenerTemporizador();

#endif

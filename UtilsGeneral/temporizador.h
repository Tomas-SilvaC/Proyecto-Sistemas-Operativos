/**************************************************************
                Pontificia Universidad Javeriana
        Autores: Gabriel Jaramillo, Juan Pabón, Tomas Silva y Felipe Rodrpiguez
        Fecha: Mayo 2025
        Materia: Sistemas Operativos
        Tema: Proyecto Final
        Fichero: temporizador.h
        Descripción: 
            Este fichero 
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

extern struct timeval tiempoInicio, tiempoFin;

void iniciarTemporizador();
double detenerTemporizador();

#endif

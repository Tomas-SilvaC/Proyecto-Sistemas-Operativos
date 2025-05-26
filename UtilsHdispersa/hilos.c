/**************************************************************
                Pontificia Universidad Javeriana
        Autores: Gabriel Jaramillo, Juan Pabón, Tomas Silva y Felipe Rodrpiguez
        Fecha: Mayo 2025
        Materia: Sistemas Operativos
        Tema: Proyecto Final
        Fichero: hilos.c
        Descripción: 
            Este fichero 
****************************************************************/

#include "hilos.h"

void *contarNoCero(void *arg) {
    DatosHilos *datos = (DatosHilos *)arg;
    int contador = 0;
    for (int i = datos->filaInicial; i < datos->filaFinal; i++) {
        for (int j = 0; j < datos->columnas; j++) {
            if (datos->matriz[i][j] != 0) {
                contador++;
            }
        }
    }
    datos->contadorNoCeros = contador;
    return NULL;
}

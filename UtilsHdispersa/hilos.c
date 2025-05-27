/**************************************************************
                Pontificia Universidad Javeriana
        Autores: Gabriel Jaramillo, Juan Pabón, Tomas Silva y Felipe Rodrpiguez
        Fecha: Mayo 2025
        Materia: Sistemas Operativos
        Tema: Proyecto Final
        Fichero: hilos.c
        Descripción: 
            Implementación de la función ejecutada por cada hilo para contar
            elementos no cero en una sección de la matriz:
            - Recorre eficientemente el rango asignado de filas
            - Actualiza el contador en la estructura compartida
            - Retorna NULL como requerido por pthread_create()
****************************************************************/

#include "hilos.h"

/* Función ejecutada por cada hilo para contar elementos no cero */
void *contarNoCero(void *arg) {
    DatosHilos *datos = (DatosHilos *)arg;
    int contador = 0; // Contador local para evitar accesos innecesarios a memoria compartida

    // Recorrido por el rango asignado de filas
    for (int i = datos->filaInicial; i < datos->filaFinal; i++) {
        for (int j = 0; j < datos->columnas; j++) {
            if (datos->matriz[i][j] != 0) {
                contador++; // Incremento en variable local
            }
        }
    }
     // Actualización final del contador en la estructura compartida
    datos->contadorNoCeros = contador;
    return NULL; // Valor de retorno requerido por pthread_create()
}

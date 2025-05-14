#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include "UtilsGeneral/utilidades.h"
#include "UtilsHdispersa/hilos.h"
#include "UtilsHdispersa/matriz.h"

int main(int argc, char *argv[]) {
    int filas = 0, columnas = 0, numHilos = 0, porcentaje = 0;
    char *nombreArchivo = NULL;

    if (procesarArgumentos(argc, argv, &filas, &columnas, &nombreArchivo, &numHilos, &porcentaje) != 0) {
        exit(EXIT_FAILURE);
    }

    int totalElementos = filas * columnas;
    int minimoCeros = ceil(totalElementos * (porcentaje / 100.0));
    int **matriz = crearMatriz(filas, columnas);

    if (cargarMatriz(nombreArchivo, matriz, filas, columnas) != 0) {
        liberarMatriz(matriz, filas);
        exit(EXIT_FAILURE);
    }

    pthread_t *hilos = malloc(numHilos * sizeof(pthread_t));
    DatosHilos *datos = malloc(numHilos * sizeof(DatosHilos));

    int filasPorHilo = filas / numHilos;
    int filasRestantes = filas % numHilos;
    int filaActual = 0;

    for (int i = 0; i < numHilos; i++) {
        int filaExtra = (i < filasRestantes) ? 1 : 0;
        datos[i].filaInicial = filaActual;
        datos[i].filaFinal = filaActual + filasPorHilo + filaExtra;
        datos[i].columnas = columnas;
        datos[i].matriz = matriz;
        datos[i].contadorNoCeros = 0;
        filaActual = datos[i].filaFinal;
        pthread_create(&hilos[i], NULL, contarNoCero, &datos[i]);
    }

    int totalNoCeros = 0;
    for (int i = 0; i < numHilos; i++) {
        pthread_join(hilos[i], NULL);
        totalNoCeros += datos[i].contadorNoCeros;
    }

    int totalCeros = totalElementos - totalNoCeros;
    double porcentajeFinal = (totalCeros * 100.0) / totalElementos;

    printf("La matriz en el archivo %s tiene un total de %d ceros (%.0f%%), ", nombreArchivo, totalCeros, porcentajeFinal);
    if (totalCeros >= minimoCeros) {
        printf("por lo tanto, se considera dispersa.\n");
    } else {
        printf("por lo tanto, no se considera dispersa.\n");
    }

    liberarMatriz(matriz, filas);
    free(hilos);
    free(datos);
    return 0;
}

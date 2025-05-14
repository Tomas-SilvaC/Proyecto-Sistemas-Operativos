#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilidades.h"

int procesarArgumentos(int argc, char *argv[], int *filas, int *columnas, char **archivo, int *hilos, int *porcentaje) {
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-f") && i + 1 < argc) {
            *filas = atoi(argv[++i]);
        } else if (!strcmp(argv[i], "-c") && i + 1 < argc) {
            *columnas = atoi(argv[++i]);
        } else if (!strcmp(argv[i], "-a") && i + 1 < argc) {
            *archivo = argv[++i];
        } else if (!strcmp(argv[i], "-n") && i + 1 < argc) {
            *hilos = atoi(argv[++i]);
        } else if (!strcmp(argv[i], "-p") && i + 1 < argc) {
            *porcentaje = atoi(argv[++i]);
        } else {
            fprintf(stderr, "Parámetro inválido o faltante: %s\n", argv[i]);
            return -1;
        }
    }

    if (*archivo == NULL || *filas <= 0 || *columnas <= 0 || *hilos <= 0 || *porcentaje < 0 || *porcentaje > 100) {
        fprintf(stderr, "Uso: ./hdispersa -f M(>0) -c N(>0) -a archivo -n hilos(>0) -p porcentaje(0-100)\n");
        return -1;
    }

    return 0;
}

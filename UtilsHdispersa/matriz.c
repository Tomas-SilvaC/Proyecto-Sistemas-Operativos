#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

int **crearMatriz(int filas, int columnas) {
    int **matriz = (int **)malloc(filas * sizeof(int *));
    for (int i = 0; i < filas; i++) {
        matriz[i] = (int *)malloc(columnas * sizeof(int));
    }
    return matriz;
}

void liberarMatriz(int **matriz, int filas) {
    for (int i = 0; i < filas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

int cargarMatriz(char *nombreArchivo, int **matriz, int filas, int columnas) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        fprintf(stderr, "Error: No se pudo abrir el archivo %s\n", nombreArchivo);
        return -1;
    }

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (fscanf(archivo, "%d", &matriz[i][j]) != 1) {
                fclose(archivo);
                fprintf(stderr, "Error leyendo el archivo: formato inválido\n");
                return -1;
            }
        }
    }

    fclose(archivo);
    return 0;
}

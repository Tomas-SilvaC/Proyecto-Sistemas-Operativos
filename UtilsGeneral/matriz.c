/**************************************************************
                Pontificia Universidad Javeriana
        Autores: Gabriel Jaramillo, Juan Pabón, Tomas Silva y Felipe Rodrpiguez
        Fecha: Mayo 2025
        Materia: Sistemas Operativos
        Tema: Proyecto Final
        Fichero: matriz.c
        Descripción: 
             Implementación de funciones básicas para manejo de matrices:
            - Creación y liberación de matrices dinámicas
            - Carga de matrices desde archivos de texto
****************************************************************/

#include "matriz.h"

/* Función que se encarga de crear una matriz
   dinámica de tamaño filas x columnas y devuelve 
   el apuntador a la matriz creada */
int **crearMatriz(int filas, int columnas) {
    int **matriz = (int **)malloc(filas * sizeof(int *));
    for (int i = 0; i < filas; i++) {
        matriz[i] = (int *)malloc(columnas * sizeof(int));
    }
    return matriz;
}

/* Función que libera la memoria ocupada por
   una matriz */
void liberarMatriz(int **matriz, int filas) {
    // Libera cada fila individualmente
    for (int i = 0; i < filas; i++) {
        free(matriz[i]);
    }
    // Libera el arreglo de apuntadores
    free(matriz);
}

/* Función que se encarga de cargar los valores de una matriz
   desde un archivo de texto dado */
int cargarMatriz(char *nombreArchivo, int **matriz, int filas, int columnas) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        fprintf(stderr, "Error: No se pudo abrir el archivo %s\n", nombreArchivo);
        return -1;
    }

    // Lectura secuencial de los valores
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

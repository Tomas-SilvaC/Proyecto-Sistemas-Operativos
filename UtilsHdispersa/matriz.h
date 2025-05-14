#ifndef MATRIZ_H
#define MATRIZ_H

int **crearMatriz(int filas, int columnas);
void liberarMatriz(int **matriz, int filas);
int cargarMatriz(char *nombreArchivo, int **matriz, int filas, int columnas);

#endif

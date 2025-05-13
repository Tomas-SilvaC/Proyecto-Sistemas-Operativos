#include <stdio.h>       // Librería estándar de entrada y salida
#include <pthread.h>     // Librería para manejo de hilos POSIX
#include <unistd.h>      // Librería para llamadas al sistema
#include <stdlib.h>      // Librería para uso de funciones como malloc, atoi, rand
#include <time.h>        // Librería para manejo de tiempo (semillas aleatorias)

typedef struct
{
    int filaInicial;
    int filaFinal;
    int columnas;
    int **matriz;
    int contadorNoCeros;
} datos_hilos;

void *contar_no_cero(void *arg){
    datos_hilos *datos = (datos_hilos *)arg;
    int contador = 0;
    for(int i=datos->filaFinal; i<datos->filaFinal; i++){
        for(int j=0; j<datos->columnas; j++){
            if(datos->matriz[i][j] != 0){
                contador++;
            }
        }
    }
    datos->contadorNoCeros = contador;
    pthread_exit(NULL);
}

int **crearMatriz(int filas, int columnas){
    int **matriz = (int**)malloc(filas*sizeof(int *));
    for(int i=0; i<columnas; i++){
        matriz[i] = (int *)malloc(columnas*sizeof(int*));
    }
    return matriz;
}

void liberarMatriz(int **matriz, int columnas){
    for(int i=0; i<columnas; i++){
        free(matriz[i]);
    }
    free(matriz);
}
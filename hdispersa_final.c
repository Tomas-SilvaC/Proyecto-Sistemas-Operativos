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

int cargarMatriz(char *nombreArchivo, int **matriz, int filas, int *columnas){
    FILE *archivo = fopen(nombreArchivo, "r");
    if(archivo == NULL){
        perror("Error al abrir el archivo.");
        return -1;
    }
    for(int i=0; i<filas; i++){
        for(int j=0; j<columnas; j++){
            if(fscanf(archivo, "%d", &matriz[i][j]) != 1){
                fclose(archivo);
                fprintf(stderr, "Error leyendo el archivo: formato inválido\n");
                return -1;
            }
        }
    }
    fclose(archivo);
    return 0;
}

int main(int argc, char *argv[]){
    int filas=0, columnas=0, numHilos=0, porcentaje=0;
    char *nombreArchivo = NULL;
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-f") && i + 1 < argc) {
            filas = atoi(argv[i++]);
        } else if (!strcmp(argv[i], "-c") && i + 1 < argc) {
            columnas = atoi(argv[i++]);
        } else if (!strcmp(argv[i], "-a") && i + 1 < argc) {
            nombreArchivo = argv[i++];
        } else if (!strcmp(argv[i], "-n") && i + 1 < argc) {
            numHilos = atoi(argv[i++]);
        } else if (!strcmp(argv[i], "-p") && i + 1 < argc) {
            porcentaje = atoi(argv[i++]);
        }
    }
    if(filas <= 0 || columnas <= 0 || numHilos <= 0 || porcentaje < 0 || porcentaje > 100){
        fprintf(stderr, "Error: Filas y columnas deben ser mayores a cero y porcentaje entre 0 y 100.\n");
        return -1;
    }
}
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
} DatosHilos;

void *contarNoCero(void *arg){
    DatosHilos *datos = (DatosHilos *)arg;
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
        fprintf(stderr, "Uso: ./hdispersa -f M(>0) -c N(>0) -a archivo -n hilos(>0) -p porcentaje(0-100)\n");
        exit(EXIT_FAILURE);
    }

    int totalElementos = filas * columnas;
    int minimoCeros = ceil(totalElementos * (porcentaje / 100.0));
    int **matriz = crearMatriz(filas, columnas);
    if(cargarMatriz(nombreArchivo, matriz, filas, columnas) != 0){
        liberarMatriz(matriz, filas);
        exit(EXIT_FAILURE);
    }

    pthread_t *hilos = (pthread_t *)malloc(numHilos * sizeof(pthread_t));
    DatosHilos *datos = (DatosHilos *)malloc(numHilos * sizeof(DatosHilos));
    int filasPorHilo = filas / numHilos;
    int filasRestantes = filas % numHilos;
    int filaActual = 0;
    for(int i=0; i<numHilos; i++){
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


    return 0;
}
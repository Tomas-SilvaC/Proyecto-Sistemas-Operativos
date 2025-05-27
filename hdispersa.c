/**************************************************************
                Pontificia Universidad Javeriana
        Autores: Gabriel Jaramillo, Juan Pabón, Tomas Silva y Felipe Rodrpiguez
        Fecha: Mayo 2025
        Materia: Sistemas Operativos
        Tema: Proyecto Final
        Fichero: hdispersa.c
        Descripción: 
            Implementación del cálculo de dispersión matricial usando hilos POSIX.
            - Crea múltiples hilos de ejecución concurrentes
            - Divide la matriz en partes iguales entre hilos
            - Utiliza memoria compartida para comunicación entre hilos
****************************************************************/
#include <pthread.h>
#include <math.h>

#include "UtilsHdispersa/hilos.h"
#include "UtilsGeneral/matriz.h"
#include "UtilsGeneral/temporizador.h"
#include "UtilsGeneral/utilidades.h"

int main(int argc, char *argv[]) {

    // Declaración de variables para parámetros de entrada
    int filas = 0, columnas = 0, numHilos = 0, porcentaje = 0;
    char *nombreArchivo = NULL;

     /* Procesamiento de argumentos de línea de comandos:
       - Valida y extrae: filas, columnas, archivo, numHilos y porcentaje
       - Sale con error si los argumentos son inválidos */
    if (procesarArgumentos(argc, argv, &filas, &columnas, &nombreArchivo, &numHilos, &porcentaje) != 0) {
        printf("Ocurrio un error...");
        exit(EXIT_FAILURE);
    }

    // Cálculo de métricas iniciales
    int totalElementos = filas * columnas;
    int minimoCeros = ceil(totalElementos * (porcentaje / 100.0));

     /* Creación y carga de la matriz:
       - Reserva memoria dinámica para la matriz 
       - Libera la memoria en caso de haber un error en la creación */
    int **matriz = crearMatriz(filas, columnas);
    if (cargarMatriz(nombreArchivo, matriz, filas, columnas) != 0) {
        liberarMatriz(matriz, filas);
        exit(EXIT_FAILURE);
    }

    // Inicio de medición de tiempo de ejecución
    iniciarTemporizador();

    printf("Se va a trabajar con %d trabajadores.\n",numHilos);

     /* Preparación de estructuras para hilos:
       - Array de identificadores de hilos
       - Array de estructuras de datos para cada hilo */
    pthread_t *hilos = malloc(numHilos * sizeof(pthread_t));
    DatosHilos *datos = malloc(numHilos * sizeof(DatosHilos));

    /* División del trabajo entre hilos:
      - Calcula filas por hilo (división equitativa)
      - Maneja filas sobrantes cuando no hay división exacta */
    int filasPorHilo = filas / numHilos;
    int filasRestantes = filas % numHilos;
    int filaActual = 0;

    /* Creación y lanzamiento de hilos:
       - Cada hilo recibe su rango de filas a procesar
       - Los primeros hilos reciben filas extra si hay sobrantes
       - Todos acceden concurrentemente a la matriz en memoria compartida */
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

    /* Sincronización y recolección de resultados:
       - Espera a que todos los hilos terminen (pthread_join)
       - Suma los contadores parciales de no-ceros */
    int totalNoCeros = 0;
    for (int i = 0; i < numHilos; i++) {
        pthread_join(hilos[i], NULL);
        totalNoCeros += datos[i].contadorNoCeros;
    }

    // Cálculo y presentación de resultados finales
    int totalCeros = totalElementos - totalNoCeros;
    double porcentajeFinal = (totalCeros * 100.0) / totalElementos;

    detenerTemporizador();

    printf("La matriz en el archivo %s tiene un total de %d ceros (%.0f%%), ", nombreArchivo, totalCeros, porcentajeFinal);
    if (totalCeros >= minimoCeros) {
        printf("por lo tanto, se considera dispersa.\n");
    } else {
        printf("por lo tanto, no se considera dispersa.\n");
    }

    // Liberación de memoria
    liberarMatriz(matriz, filas);
    free(hilos);
    free(datos);
    
    return 0;
}

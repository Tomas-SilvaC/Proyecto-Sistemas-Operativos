/**************************************************************
                Pontificia Universidad Javeriana
        Autores: Gabriel Jaramillo, Juan Pabón, Tomas Silva y Felipe Rodrpiguez
        Fecha: Mayo 2025
        Materia: Sistemas Operativos
        Tema: Proyecto Final
        Fichero: pdispersa.c
        Descripción: 
            Implementación del cálculo de dispersión matricial usando procesos.
            - Crea múltiples procesos hijos mediante fork()
            - Divide la matriz en partes iguales entre procesos
            - Usa archivos temporales para comunicación interprocesos
            - Calcula porcentaje de ceros para determinar dispersión
            - Valida parámetros de entrada y maneja errores
****************************************************************/

#include "UtilsGeneral/utilidades.h"
#include "UtilsGeneral/matriz.h"
#include "UtilsGeneral/temporizador.h"
#include "UtilsPdispersa/procesos.h"

#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <math.h>

int main(int argc, char *argv[])
{
    // Declaración de variables para parámetros de entrada
    int filas = 0, columnas = 0, numProcesos= 0, porcentaje = 0;
    char *nombreArchivo = NULL;

   /* Procesamiento de argumentos de línea de comandos:
       - Valida y extrae: filas, columnas, archivo, numProcesos y porcentaje
       - Sale con error si los argumentos son inválidos */
    if(procesarArgumentos(argc, argv, &filas, &columnas, &nombreArchivo, &numProcesos, &porcentaje) != 0)
    {
        printf("Ocurrion un error...");
        exit(EXIT_FAILURE);
    }
    int totalElementos = filas * columnas;
    int minimoCeros = ceil(totalElementos * (porcentaje / 100.0));

    /* Creación y carga de la matriz:
       - Reserva memoria dinámica para la matriz
       - Libera la memoria en caso de haber un error al crearla */
    int **matriz = crearMatriz(filas, columnas);
    if (cargarMatriz(nombreArchivo, matriz, filas, columnas) != 0) {
        liberarMatriz(matriz, filas);
        exit(EXIT_FAILURE);
    }

    // Inicio de medición de tiempo de ejecución
    iniciarTemporizador();

    /* División del trabajo entre procesos:
       - Calcula filas por proceso
       - Calcula la cantidad de filas sobrantes cuando no hay división exacta */
    printf("Se va trabajar con %d procesos.\n",numProcesos);
    pid_t filPorProceso = filas/numProcesos;
    pid_t filsExtra = filas%numProcesos;

    // Arreglo de los procesos hijos
    pid_t *pids = (pid_t*) malloc(numProcesos * sizeof(pid_t));
    DatosProcesos *datos = malloc(numProcesos * sizeof(DatosProcesos));
    if (pids==NULL)
    {
        perror("Error al asignar memoria.\n");
    }

    /* Creación de procesos hijos:
       - Cada hijo procesa un bloque de filas
       - Se pasan parámetros mediante estructura DatosProcesos
       - Procesos sobrantes reciben una fila adicional */
    int filaActual = 0;
    for(int i=0;i< numProcesos;i++)
    {
        int filaExtra = (i < filsExtra) ? 1 : 0;
        datos[i].filaInicial = filaActual;
        datos[i].filaFinal = filaActual + filPorProceso + filaExtra;
        datos[i].columnas = columnas;
        datos[i].matriz = matriz;
        datos[i].contadorNoCeros = 0;
        filaActual = datos[i].filaFinal;
        pids[i] = fork();
        // Verifica si es el proceso hijo
        if(pids[i]==0)
        {
            funcProceso(datos[i]);
        } // Verifica si hubo un error al hacer el fork
        else if(pids[i]<0)
        {
            perror("No se pudo crear el proceso hijo.");
            exit(EXIT_FAILURE);
        }
    }

    /* Recolección de resultados:
       - Espera la finalización de todos los procesos hijos
       - Lee resultados de archivos temporales cuando es necesario
       - Valida códigos de salida de los procesos */
    int totalNoCeros = 0;
    for(int i=0; i <numProcesos; i++)
    {
        int estado;
        waitpid(pids[i], &estado, 0);

        if(WIFEXITED(estado))
        {
            int codSalida = WEXITSTATUS(estado);
            if(codSalida >= 255) // Comunicación mediante archivo
            {
                char nomArchivo[256];
                sprintf(nomArchivo, ARCHIVO_PATRON, pids[i]);
                FILE *file = fopen(nomArchivo, "r");
                if(file)
                {
                    int cuenta;
                    fscanf(file,"%d", &cuenta);
                    fclose(file);
                    remove(nomArchivo);
                    totalNoCeros += cuenta;
                }
            }
            else{ // Comunicación mediante código de salida
                totalNoCeros += codSalida;
            }
        }
    }

    // Cálculo y presentación de resultados finales
    int totalCeros = totalElementos - totalNoCeros;
    double porcentajeFinal = (totalCeros * 100.0)/ totalElementos;

    detenerTemporizador();

    printf("La matriz en el archivo %s tiene un total de %d ceros (%.0f%%), ", nombreArchivo, totalCeros, porcentajeFinal);
    if (totalCeros >= minimoCeros) {
        printf("por lo tanto, se considera dispersa.\n");
    } else {
        printf("por lo tanto, no se considera dispersa.\n");
    }

     // Liberación de la memoria
    liberarMatriz(matriz, filas);
    free(pids);
    free(datos);

    return 0;
}

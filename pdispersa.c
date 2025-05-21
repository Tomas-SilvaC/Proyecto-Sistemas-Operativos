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
    int filas = 0, columnas = 0, numProcesos= 0, porcentaje = 0;
    char *nombreArchivo = NULL;
    if(procesarArgumentos(argc, argv, &filas, &columnas, &nombreArchivo, &numProcesos, &porcentaje) != 0)
    {
        printf("Ocurrion un error...");
        exit(EXIT_FAILURE);
    }
    int totalElementos = filas * columnas;
    int minimoCeros = ceil(totalElementos * (porcentaje / 100.0));
    int **matriz = crearMatriz(filas, columnas);

    if (cargarMatriz(nombreArchivo, matriz, filas, columnas) != 0) {
        liberarMatriz(matriz, filas);
        exit(EXIT_FAILURE);
    }

    iniciarTemporizador();

    //calcular filas por proceso
    
    printf("Se va trabajar con %d procesos.\n",numProcesos);
    pid_t filPorProceso = filas/numProcesos;
    pid_t filsExtra = filas%numProcesos;

    //conjunto de los procesos hijos
    pid_t *pids = (pid_t*) malloc(numProcesos * sizeof(pid_t));
    DatosProcesos *datos = malloc(numProcesos * sizeof(DatosProcesos));
    if (pids==NULL)
    {
        perror("Error al asignar memoria.\n");
    }
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
        if(pids[i]==0)
        {
            funcProceso(datos[i]);
        }
        else if(pids[i]<0)
        {
            perror("No se pudo crear el proceso hijo.");
            exit(EXIT_FAILURE);
        }
    }
    int totalNoCeros = 0;
    for(int i=0; i <numProcesos; i++)
    {
        int estado;
        waitpid(pids[i], &estado, 0);

        if(WIFEXITED(estado))
        {
            int codSalida = WEXITSTATUS(estado);
            if(codSalida >= 255)
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
            else{
                totalNoCeros += codSalida;
            }
        }
    }

    int totalCeros = totalElementos - totalNoCeros;
    double porcentajeFinal = (totalCeros * 100.0)/ totalElementos;

    detenerTemporizador();

    printf("La matriz en el archivo %s tiene un total de %d ceros (%.0f%%), ", nombreArchivo, totalCeros, porcentajeFinal);
    if (totalCeros >= minimoCeros) {
        printf("por lo tanto, se considera dispersa.\n");
    } else {
        printf("por lo tanto, no se considera dispersa.\n");
    }

    liberarMatriz(matriz, filas);
    free(pids);
    free(datos);

    return 0;
}
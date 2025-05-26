/**************************************************************
                Pontificia Universidad Javeriana
        Autores: Gabriel Jaramillo, Juan Pabón, Tomas Silva y Felipe Rodrpiguez
        Fecha: Mayo 2025
        Materia: Sistemas Operativos
        Tema: Proyecto Final
        Fichero: procesos.c
        Descripción: 
            Este fichero 
****************************************************************/

#include "procesos.h"

int contarNoCero(DatosProcesos arg) {
    DatosProcesos datos = arg;
    int contador = 0;
    for (int i = datos.filaInicial; i < datos.filaFinal; i++) {
        for (int j = 0; j < datos.columnas; j++) {
            if (datos.matriz[i][j] != 0) {
                contador++;
            }
        }
    }
    datos.contadorNoCeros = contador;
    return contador;
}

void funcProceso(DatosProcesos arg)
{
    int cuenta = contarNoCero(arg);
    if(cuenta<=254)
    {
        exit(cuenta);
    }
    else{
        char filename[256];
        sprintf(filename, ARCHIVO_PATRON, getpid());
        FILE *file = fopen(filename, "w");
        if(file)
        {
            fprintf(file, "%d", cuenta);
            fclose(file);
        }
        exit(255);
    }
}

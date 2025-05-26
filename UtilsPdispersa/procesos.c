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

/* Cuenta los elementos no cero en un segmento
   de matriz */
int contarNoCero(DatosProcesos arg) {
    DatosProcesos datos = arg;
    int contador = 0; // Variable local para almacenar la cantidad de elementos no ceros

    // Recorrido del segmento de matriz asignado
    for (int i = datos.filaInicial; i < datos.filaFinal; i++) {
        for (int j = 0; j < datos.columnas; j++) {
            if (datos.matriz[i][j] != 0) {
                contador++; // Aumenta la variable local
            }
        }
    }
    datos.contadorNoCeros = contador;
    return contador;
}

/* Función principal ejecutada por cada proceso hijo */
void funcProceso(DatosProcesos arg)
{
    int cuenta = contarNoCero(arg);

    // Comunicación de resultados
    if(cuenta<=254)
    {
        // Resultado pequeño: usar código de salida directamente
        exit(cuenta);
    }
    else{
        // Resultado grande: usar archivo temporal
        char filename[256];
        sprintf(filename, ARCHIVO_PATRON, getpid());
        FILE *file = fopen(filename, "w");
        if(file)
        {
            fprintf(file, "%d", cuenta);
            fclose(file);
        }
        // Código especial para indicar que el resultado está en archivo
        exit(255);
    }
}

/**************************************************************
                Pontificia Universidad Javeriana
        Autores: Gabriel Jaramillo, Juan Pabón, Tomas Silva y Felipe Rodrpiguez
        Fecha: Mayo 2025
        Materia: Sistemas Operativos
        Tema: Proyecto Final
        Fichero: utilidades.c
        Descripción: 
          Implementación del procesamiento de argumentos de línea de comandos:
            - Validación y extracción de parámetros de entrada
            - Verificación de valores dentro de rangos aceptables
            - Generación de mensajes de error descriptivos
            - Soporte para ambos programas (hdispersa y pdispersa)
****************************************************************/

#include "utilidades.h"

/* Función que procesa y valida los argumentos
   de la linea de comandos */
int procesarArgumentos(int argc, char *argv[], int *filas, int *columnas, char **archivo, int *hilos, int *porcentaje) {

    // Procesamiento de cada argumento
    for (int i = 1; i < argc; i++) {
      
        if (!strcmp(argv[i], "-f") && i + 1 < argc) {
            *filas = atoi(argv[++i]);
        } else if (!strcmp(argv[i], "-c") && i + 1 < argc) {
            *columnas = atoi(argv[++i]);
        } else if (!strcmp(argv[i], "-a") && i + 1 < argc) {
            *archivo = argv[++i];
        } else if (!strcmp(argv[i], "-n") && i + 1 < argc) {
            *hilos = atoi(argv[++i]);
        } else if (!strcmp(argv[i], "-p") && i + 1 < argc) {
            *porcentaje = atoi(argv[++i]);
        } else {
            fprintf(stderr, "Parámetro inválido o faltante: %s\n", argv[i]);
            return -1;
        }

    }

   /* Validación final de parámetros:
       - Todos los parámetros obligatorios deben estar presentes
       - Valores deben estar en rangos aceptables */
    if (*archivo == NULL || *filas <= 0 || *columnas <= 0 || *hilos <= 0 || *porcentaje < 0 || *porcentaje > 100) {
        fprintf(stderr, "Uso: ./hdispersa -f M(>0) -c N(>0) -a archivo -n hilos(>0) -p porcentaje(0-100)\n");
        return -1;
    }

    return 0;
}

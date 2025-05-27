# **************************************************************
#                 Pontificia Universidad Javeriana
#         Autores: Gabriel Jaramillo, Juan Pabón, Tomas Silva y Felipe Rodriguez
#         Fecha: Mayo 2025
#         Materia: Sistemas Operativos
#         Tema: Proyecto Final
#         Fichero: Makefile
#         Descripción: 
#             Makefile para automatización del proceso de compilación.
#             - Compila los programas principales (hdispersa, pdispersa)
#             - Construye el generador de matrices
#             - Gestiona dependencias entre módulos
#             - Proporciona limpieza de archivos temporales
# **************************************************************

# Configuración del compilador
CC = gcc
CXX = g++
CFLAGS = -Wall -lm
PTHREAD = -lpthread

# Carpetas
UTILS_GENERAL = UtilsGeneral
UTILS_HDISPERSA = UtilsHdispersa
UTILS_PDISPERSA = UtilsPdispersa

# Archivos objeto comunes
GENERAL_OBJS = $(UTILS_GENERAL)/matriz.o $(UTILS_GENERAL)/temporizador.o $(UTILS_GENERAL)/utilidades.o

# Archivos objeto específicos
HDISPERSA_OBJS = $(UTILS_HDISPERSA)/hilos.o
PDISPERSA_OBJS = $(UTILS_PDISPERSA)/procesos.o

# Objetivos
all: hdispersa pdispersa generador

# Programa con implementación de hilos
hdispersa: hdispersa.c $(GENERAL_OBJS) $(HDISPERSA_OBJS)
	$(CC) -o hdispersa hdispersa.c $(GENERAL_OBJS) $(HDISPERSA_OBJS) $(CFLAGS) $(PTHREAD)

# Programa con implementación de procesos
pdispersa: pdispersa.c $(GENERAL_OBJS) $(PDISPERSA_OBJS)
	$(CC) -o pdispersa pdispersa.c $(GENERAL_OBJS) $(PDISPERSA_OBJS) $(CFLAGS)

# Generador de matrices (escrito en C++)
generador: generadormatrices.cpp
	$(CXX) -o generador generadormatrices.cpp

# Regla para compilar archivos .c a .o
%.o: %.c
	$(CC) -c $< -o $@

# Limpieza de archivos generados
clean:
	rm -f hdispersa pdispersa generador
	rm -f $(UTILS_GENERAL)/*.o $(UTILS_HDISPERSA)/*.o $(UTILS_PDISPERSA)/*.o
	rm -f *.txt
	rm -f *.dat

.PHONY: all clean

# Compiladores
CC = gcc
CXX = g++

# Flags generales
CFLAGS = -Wall -IUtilsGeneral -IUtilsHdispersa -IUtilsPdispersa

# Archivos fuente comunes
UTILS_GENERAL = UtilsGeneral/matriz.c UtilsGeneral/temporizador.c UtilsGeneral/utilidades.c

# Objetivo por defecto
all: hdispersa pdispersa generador

# Compilación de hdispersa (usa math.h y pthread)
hdispersa: hdispersa.c UtilsHdispersa/hilos.c $(UTILS_GENERAL)
	$(CC) $(CFLAGS) -o hdispersa hdispersa.c UtilsHdispersa/hilos.c $(UTILS_GENERAL) -lm -lpthread

# Compilación de pdispersa (usa math.h)
pdispersa: pdispersa.c UtilsPdispersa/procesos.c $(UTILS_GENERAL)
	$(CC) $(CFLAGS) -o pdispersa pdispersa.c UtilsPdispersa/procesos.c $(UTILS_GENERAL) -lm

# Compilación del generador de matrices (escrito en C++)
generador: generadormatrices.cpp
	$(CXX) -Wall -o generador generadormatrices.cpp

# Limpieza
clean:
	rm -f hdispersa pdispersa generador

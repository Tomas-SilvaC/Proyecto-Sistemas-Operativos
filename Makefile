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

hdispersa: hdispersa.c $(GENERAL_OBJS) $(HDISPERSA_OBJS)
	$(CC) -o hdispersa hdispersa.c $(GENERAL_OBJS) $(HDISPERSA_OBJS) $(CFLAGS) $(PTHREAD)

pdispersa: pdispersa.c $(GENERAL_OBJS) $(PDISPERSA_OBJS)
	$(CC) -o pdispersa pdispersa.c $(GENERAL_OBJS) $(PDISPERSA_OBJS) $(CFLAGS)

generador: generadormatrices.cpp
	$(CXX) -o generador generadormatrices.cpp

# Regla para compilar archivos .c a .o
%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f hdispersa pdispersa generador
	rm -f $(UTILS_GENERAL)/*.o $(UTILS_HDISPERSA)/*.o $(UTILS_PDISPERSA)/*.o
	rm -f matriz.txt
	rm -f *.dat

.PHONY: all clean
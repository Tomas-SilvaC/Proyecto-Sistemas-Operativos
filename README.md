# Proyecto de sistemas operativos (Hdispersa y Pdispersa)

Pontificia Universidad Javeriana  
Asignatura: Sistemas Operativos  
Profesor: John Jairo Corredor Franco  

## Autores
- Gabriel Jaramillo Cuberos  
- Juan Pabón Vargas  
- Tomás Silva  
- Felipe Rodríguez  

---

## 📌 Descripción

Este proyecto implementa dos programas concurrentes para determinar si una matriz es dispersa (es decir, si contiene una gran cantidad de ceros).  
Se desarrollaron dos versiones:

- `hdispersa`: basada en hilos POSIX.
- `pdispersa`: basada en procesos con `fork()`.

Ambos programas analizan matrices cargadas desde archivos de texto, y dividen el trabajo entre múltiples trabajadores para aprovechar el paralelismo.

---

## ⚙️ Compilación

```bash
# Compilar hdispersa
gcc -o hdispersa hdispersa.c UtilsHdispersa/hilos.c UtilsGeneral/matriz.c UtilsGeneral/temporizador.c UtilsGeneral/utilidades.c -lpthread -lm

# Compilar pdispersa
gcc -o pdispersa pdispersa.c UtilsPdispersa/procesos.c UtilsGeneral/matriz.c UtilsGeneral/temporizador.c UtilsGeneral/utilidades.c -lpthread -lm

# Compilar generador de matrices
g++ -o generador generadormatrices.cpp
```
## 🏃‍♂️Ejecución

```bash
# Ejecutar hdispersa
./hdispersa -f <Filas> -c <Columnas> -a <ArchivoMatriz> -n <Workers> -p <Porcentaje>

# Ejecutar pdispersa
./pdispersa -f <Filas> -c <Columnas> -a <ArchivoMatriz> -n <Workers> -p <Porcentaje>

# Ejecutar generador de matrices
./generador [opción]

# Dar permisos al script lanzador
chmod +x lanza.pl

# Ejecutar script lanzador
./lanza.pl

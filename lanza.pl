#!/usr/bin/perl
# **************************************************************
#                 Pontificia Universidad Javeriana
#         Autores: Gabriel Jaramillo, Juan Pabón, Tomas Silva y Felipe Rodriguez
#         Fecha: Mayo 2025
#         Materia: Sistemas Operativos
#         Tema: Proyecto Final
#         Fichero: lanza.pl
#         Descripción: 
#              Script de automatización para pruebas de rendimiento comparativas.
#             - Genera matrices de prueba de diferentes tamaños
#             - Ejecuta múltiples iteraciones de hdispersa y pdispersa
#             - Varía el número de trabajadores (1-16) en cada ejecución
#             - Almacena resultados en archivos .dat para análisis posterior
#             - Realiza limpieza automática de archivos temporales
# **************************************************************

use strict;
use warnings;

# Obtiene la ruta del directorio actual
my $Path = `pwd`;
chomp($Path);

# Configuración de las pruebas
my @nombreEjecutable = ("hdispersa","pdispersa"); # Programas a evaluar
my $Repeticiones = 16; # Número de iteraciones

# Tamaños de matriz a evaluar
my @tamanos = (1000, 2000, 5000, 8000, 10000);

# Ejecutar generador con opción 2
print "Generando matrices con ./generador 2...\n";
system("./generador 2") == 0 or die "Error al ejecutar el generador\n";

# Ejecutar cada programa para cada tamaño
foreach my $tam (@tamanos) {
    foreach my $ejecutable (@nombreEjecutable) {
        my $archivo = "$Path/$ejecutable.-$tam.dat"; # Archivo de salida para resultados

        open(my $fh, '>', $archivo) or die "No se pudo crear el archivo $archivo: $!";
        
        # Ejecución con incremento progresivo de workers (1-16)
        for (my $i = 1; $i <= $Repeticiones; $i++) {
            print "Ejecutando $ejecutable con matriz${tam}.txt, repetición $i...\n";

            my $comando = "./$ejecutable -f $tam -c $tam -a matriz${tam}.txt -n $i -p 72";
            my $salida = `$comando`;

            print $fh "Ejecución $i:\n$salida\n"; # Registro en archivo .dat
        }

        close($fh);
    }
}

# Eliminar matrices generadas
foreach my $tam (@tamanos) {
    my $archivo = "matriz${tam}.txt";
    if (-e $archivo) {
        unlink $archivo or warn "No se pudo eliminar $archivo: $!";
    }
}

print "Fin de la ejecución de todos los ejecutables y limpieza de archivos.\n";

#!/usr/bin/perl

use strict;
use warnings;

my $Path = `pwd`;
chomp($Path);

# Lista de ejecutables
my @nombreEjecutable = ("hdispersa","pdispersa");
my $Repeticiones = 16;

# Tamaños de matriz a evaluar
my @tamanos = (1000, 2000, 5000, 8000, 10000);

# Ejecutar generador con opción 2
print "Generando matrices con ./generador 2...\n";
system("./generador 2") == 0 or die "Error al ejecutar el generador\n";

# Ejecutar cada binario para cada tamaño
foreach my $tam (@tamanos) {
    foreach my $ejecutable (@nombreEjecutable) {
        my $archivo = "$Path/$ejecutable.-$tam.dat";

        open(my $fh, '>', $archivo) or die "No se pudo crear el archivo $archivo: $!";

        for (my $i = 1; $i <= $Repeticiones; $i++) {
            print "Ejecutando $ejecutable con matriz${tam}.txt, repetición $i...\n";

            my $comando = "./$ejecutable -f $tam -c $tam -a matriz${tam}.txt -n $i -p 72";
            my $salida = `$comando`;

            print $fh "Ejecución $i:\n$salida\n";
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

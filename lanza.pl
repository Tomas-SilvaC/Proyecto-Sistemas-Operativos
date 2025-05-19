#!/usr/bin/perl

use strict;
use warnings;

my $Path = `pwd`;
chomp($Path);

# Lista de ejecutables
my @nombreEjecutable = ("hdispersa");
my $Repeticiones = 16;

foreach my $ejecutable (@nombreEjecutable) {
    my $archivo = "$Path/$ejecutable.dat";

    open(my $fh, '>', $archivo) or die "No se pudo crear el archivo $archivo: $!";

    for (my $i = 1; $i <= $Repeticiones; $i++) {
        print "Ejecutando $ejecutable, repetición $i...\n";

        # Ejecución de los programas
        my $comando = "./$ejecutable -f 10000 -c 10000 -a matriz10000.txt -n $i -p 72";

        # Ejecutar y capturar salida
        my $salida = `$comando`;
        print $fh "Ejecución $i:\n$salida\n";
    }

    close($fh);
}

print "Fin de la ejecución de todos los ejecutables\n";

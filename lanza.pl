#!/usr/bin/perl 

$Path = `pwd`;
chomp($Path);
@Ejecutable = ("hdispersa");
$Repeticiones = 30;

foreach $Ejecutable (@Ejecutable) {
    $Ejecutable = $Path . "/" . $Ejecutable;
    print "Ejecutando $Ejecutable\n";
    $file = "$Path/$Ejecutable-".$Ejecutable."-Hilos-".
    for ($i=0; $i<$Repeticiones; $i++) {
        system("./$Ejecutable -f 10000 -c 10000 -a matriz.txt -n $i -p 70");
    }
    print "Fin de la ejecucion de $Ejecutable\n";
}

print "Fin de la ejecucion de todos los ejecutables\n";
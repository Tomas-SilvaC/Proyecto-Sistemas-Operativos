#!/usr/bin/perl 

$Path = `pwd`;
chomp($Path);
@nombreEjecutable = ("hdispersa");
$Repeticiones = 30;

foreach $ejecutabable (@nombreEjecutable){
    for($i = 1; $i<=$Repeticiones; $i++){
    system("./hdispersa -f 10000 -c 10000 -a matriz.txt -n $i -p 72)");
}
}



print "Fin de la ejecucion de todos los ejecutables\n";
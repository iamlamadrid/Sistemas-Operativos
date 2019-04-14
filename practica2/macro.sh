#!/bin/bash
touch resultados.txt
chmod 666 'resultados.txt'
for ((i=10; i <= 200; i=i+10 ))
do
    ./programa $i -5 5 >> 'resultados.txt'
    echo Ejecutado con $i hijos
done
echo Fin de la ejecucion

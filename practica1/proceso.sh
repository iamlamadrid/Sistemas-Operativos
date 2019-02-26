#!/bin/bash
if [ $NUM_ITERACIONES = NULL ] 
then
	$NUM_ITERACIONES=10
fi
for i in $(seq 1 $NUM_ITERACIONES) ; do
	./generador > datos$i
	sleep 1.0
	echo Datos[$i] realizado con éxito
done
for i in $(seq 1 $NUM_ITERACIONES)
do
	./filtro 1000 < datos$i 2>> filtrado.stderr >> salida.stdout
	echo Filtro[$i] realizado con éxito	
done

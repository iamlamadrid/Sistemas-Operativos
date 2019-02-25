#!/bin/bash
NUM_ITERACIONES=10
for i in $(seq 1 $NUM_ITERACIONES) ; do
	./generador > datos$i
	sleep 1.0
	echo Datos[$i] realizado con éxito
done
for i in $(seq 1 $NUM_ITERACIONES)
do
	./filtro 1000 < datos$i > (salida.stdout || filtrado.stderr)
	echo Filtro[$i] realizado con éxito	
done

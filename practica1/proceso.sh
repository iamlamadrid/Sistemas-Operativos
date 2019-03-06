#!/bin/bash
#si NUM_ITERACIONES no tiene ningun valor le damos 10 por defecto
if [ -z "${NUM_ITERACIONES}" ] 
then
	NUM_ITERACIONES=10
fi
# hacemos el generador num iteraciones con una espera de un segundo
for i in $(seq 1 $NUM_ITERACIONES) ; do
	./generador > datos$i
	sleep 1.0
	echo Datos[$i] realizado con éxito
done
# y, a continuación, filtramos todos los archivos creados previamente
for i in $(seq 1 $NUM_ITERACIONES)
do
	./filtro 1000 < datos$i 2>> filtrado.stderr >> salida.stdout
	echo Filtro[$i] realizado con éxito	
done 
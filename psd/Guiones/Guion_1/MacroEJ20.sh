#!/bin/bash
MENSAJE='1'
read nomFich
echo El directorio es $nomFich
if [ $MENSAJE -eq '1' ]
then
	for i in $@
	do 
		if test -e $i
		then
			echo El tamaño de $i ocupa $(stat -c %s $i) bytes;
		else
			echo No existe el fichero $i
		fi
	done

else
	echo La variable mensaje no tiene el valor deseado

fi


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

/*
	Programa principal
*/
void main(){
	// creamos tuberia
	double pipePaH[3];
	double pipeHaP[2];

	// creamos proceso
	pid_t pid;

	// creamos los hijos
	int numProc = 1;
	for( numProc ; numProc=N_WORKERS ; numProc++ ){
		pid = fork();
		if ( pid == -1){
			printf("Error al crear el hijo numero %d\n",numProc);
		}
	}

	// sincornizamos porcesos
	if ( pid == 0 ) {	// si es hijo 

	} else if( pid > 0 ) {	// si es padre

	}	
}

/*
	Metodo que calcula la funcion dada 
*/
double calc_function(double x){
	double valor;
	if(x==0){
		valor = 1;
	}else{
		valor = x*sin(25/x);
	}
	return valor;
}
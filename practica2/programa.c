/* ********************************************************** */
/* --------- ASIGNATURA: Sistemas Operativos (G660) --------- */
/* ********************************************************** */
/* -------------- AUTOR: ÁLvaro Lamadrid Agudo -------------- */
/* ********************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

double calc_function(double x);
double calculaArea(double x_ini, double w, int pasos);
/*
	Programa principal
*/
int main(int argc, const char *argv[])
{
	

	// datos
	double x_ini;
	int pasos;
	int N_WORKERS = atoi(argv[1]); // numerod e procesos hijos que van a trabajar
	double a = atoi(argv[2]); // primer limite
	double b = atoi(argv[3]); // segundo limite
	double areatotal = 0;
	char buffer[N_WORKERS*3];
	double area_calculada = 0;

	// creamos tuberia
	int pipePaH[N_WORKERS][2]; // tuberia de padre a hijo (envio de datos)
	int pipeHaP[N_WORKERS][2]; // tuberia de hijo a padre (envio de resultados)

	// creamos proceso
	pid_t pid;

	// calculo del ancho
	double w = (b-a)/N_WORKERS;

	// creamos los hijos
	int numProc = 1;
	for( numProc ; numProc=N_WORKERS ; numProc++ ){
		printf("llego hasta 1\n");
		pid = fork();
		if ( pid == -1){
			printf("Error al crear el hijo numero %d\n",numProc);
		}
		
		if(  -1 == pipe(pipePaH[numProc]) || -1==pipe(pipeHaP[numProc])  ) {
			printf("Error en la creación de la tubería número: %d",numProc);
		}
		printf("llego hasta 2\n");
		// sincornizamos porcesos
		if ( pid == 0 ) {	// si es hijo 
			printf("llego hasta 5\n");
			close(pipeHaP[numProc][1]);
			printf("llego hasta 5.1\n");
			read(pipePaH[numProc][0], &x_ini, sizeof(double));
			printf("llego hasta 5.115\n");
			puts(buffer);
			printf("llego hasta 5.12\n");
		    read(pipePaH[numProc][0], &w, sizeof(double));
		    puts(buffer);
		    read(pipePaH[numProc][0], &pasos, sizeof(int));
		    puts(buffer);
		    printf("llego hasta 5.15\n");
		    area_calculada = calculaArea(x_ini, w, pasos);
		    printf("llego hasta 5.2\n");
		    write(pipeHaP[numProc][1], &area_calculada, sizeof(double));
		    printf("llego hasta 6\n");
		    exit(-1);

		} else if( pid > 0 ) {	// si es padre
			printf("llego hasta 3\n");
			close(pipeHaP[numProc][0]);
			write(pipePaH[numProc][1], &x_ini, sizeof(double));
		    write(pipePaH[numProc][1], &w, sizeof(double));
		    write(pipePaH[numProc][1], &pasos, sizeof(int));
		    printf("llego hasta 4\n");
		    wait(&pid);
		    printf("llego hasta 7\n");
		    read(pipeHaP[numProc][0], &area_calculada, sizeof(double));
			puts(buffer);
			areatotal += area_calculada;
			printf("%f\n", areatotal);
		}	

		w+=x_ini;
	}

	/*
		Cuando creamos una pipe:
			0 - Es por donde se le lee
			1 - Es por donde se escribe.
	
		Estamos definiendo la direccion de comunicacion de la pipe. En el canal P->H
		el padre hablara y el hijo escuchara, por lo que es tonteria en el hijo tener
		abierto el canal de escritura de una pipe donde solo puede leer. close(pipePaH[1]);

		Ademas cerramos el canal de lectura de la pipe H a P, puesto que en ese canal el 
		hijo solo va a escribir, no va a leer (a tiene la otra pipe para ello).
		
		Lo mismo pasara en el padre (cerrando el canal que toque).
	*/

	// sincornizamos porcesos
	/*if ( pid == 0 ) {	// si es hijo 
		read(pipePaH[0], &x_ini, sizeof(double));
	    read(pipePaH[0], &w, sizeof(double));
	    read(pipePaH[0], &pasos, sizeof(int));
	    
		// procesamos los datos llegados
		// abrimos la tuberia de escritura al padre
		// cerramos el proceso
	} else if( pid > 0 ) {	// si es padre
		write(pipePaH[1], &x_ini, sizeof(double));
	    write(pipePaH[1], &w, sizeof(double));
	    write(pipePaH[1], &pasos, sizeof(int));
		wait();
	}	*/
}

/*
	 “calc_function”, la cual recibe como parámetro
	 el valor “x” y devuelve el f(x) correspondiente
*/
double calc_function(double x){
	double valor; // valor de f(x) 
	// si la x vale 0 retornamos 1 como se indica en el enunciado
	if(x==0){
		valor = 1;
	}else{
		valor = x*sin(25/x); // 𝑓(𝑥) = 𝑥∙sin(25/x)
	}
	return valor;
}

/*

*/
double calculaArea(double x_ini, double w, int pasos){
	// calculo del ancho de cada trapecio
	double valor;
	double wlocal = w/(double)pasos;
	for(int i=0 ; i<pasos; i++){
		double fx = calc_function(x_ini);
		double fxa = calc_function(x_ini + wlocal);
		double area = ((fx +fxa)/2)*x_ini;
		valor += area;
		x_ini += wlocal;
	}
	//fprintf(stdout, "%f\n", valor);
	return valor;
}
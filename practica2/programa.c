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
#include "constantes.h"

double calc_function(double x);
void manejadorSU1();

/*
	Programa principal
*/
int main(int argc, const char *argv[])
{
	
	// datos	
	int N_WORKERS = atoi(argv[1]); // numero de procesos hijos que van a trabajar
	double a = atoi(argv[2]); // primer limite
	double b = atoi(argv[3]); // segundo limite
	if(a > b){
		a=atoi(argv[3]);
		b = atoi(argv[2]);
	}
	double areatotal = 0; // area total de la función
	double x_ini = a; // la x inicial que es el parámetro que le pasamos
	double area_calculada = 0; // area que va calculando cada hijo
	signal(SIGUSR1,manejadorSU1); // señal que manda el hijo al padre cada vez que se pasa por 0
	double valor_de_area; // -1 0 1 dependiendo de si el area es negativa, positiva o 0
	int ceros_totales = 0; // veces que se pasa por el eje 'y'
	int pasos = PASOS; // creamos la constante para usarla en read y write

	// creamos tuberia
	int pipePaH[N_WORKERS][2]; // tuberia de padre a hijo (envio de datos)
	int pipeHaP[N_WORKERS][2]; // tuberia de hijo a padre (envio de resultados)

	// creamos proceso
	pid_t pid;

	// calculo del ancho
	double w = (b-a)/N_WORKERS;

	for(int numProc=0 ; numProc<N_WORKERS ; numProc++ ){
		//creamos las tuberias
		if(  -1 == pipe(pipePaH[numProc]) || -1==pipe(pipeHaP[numProc])  ) {
			printf("Error en la creación de la tubería número: %d",numProc);
		}
		pid = fork(); // creamos el hijo
		// comprobamos si hay algun error
		if ( pid == -1){
			printf("Error al crear el hijo numero %d\n",numProc);
		}
		// sincornizamos porcesos
		if ( pid == 0 ) {	// si es hijo 
			// cerramos las tuberias
		    close(pipePaH[numProc][1]);
		    close(pipeHaP[numProc][0]);

		    // leemos los datos pasados por el padre
			read(pipePaH[numProc][0], &x_ini, sizeof(double));
		    read(pipePaH[numProc][0], &w, sizeof(double));
		    read(pipePaH[numProc][0], &pasos, sizeof(int));

			double wlocal = w/(double)PASOS; // ancho de cada paso dentro del hijo
			int ceros=0;
			for(int i=0 ; i<PASOS; i++){
				double fx = calc_function(x_ini);
				double fxa = calc_function(x_ini + wlocal);
				double area = ((fx +fxa)/2)*wlocal;
				area_calculada += area;
				x_ini += wlocal;
				// comprobamos si pasa por el eje 'y'
				if ((fx*fxa)<0.0){
		            ceros++;
		            kill(getppid(),SIGUSR1); // mandamos la señas al padre
		        }		        
			}

			// escribimos los resultados en la tuberia
		    write(pipeHaP[numProc][1], &area_calculada, sizeof(double));
		    write(pipeHaP[numProc][1], &ceros, sizeof(int));

		    // comprobamos si el area calculada ha sido negativa o positiva
		    if(area_calculada < 0){
		    	valor_de_area = -1;
		    }else if(area_calculada == 0){
		    	valor_de_area = 0;
		    }else if(area_calculada > 0){
		    	valor_de_area = 1;
		    }
		    write(pipeHaP[numProc][1], &valor_de_area, sizeof(double));

		    exit(0); // el hijo termina su trabajo

		} else if( pid > 0 ) {	// si es padre
			double area_calculada = 0.0;
			int ceros = 0;

			// cerramos tuberias
			close(pipePaH[numProc][0]);
			close(pipeHaP[numProc][1]);

			// mandamos al hijo los datos que debe procesar
			write(pipePaH[numProc][1], &x_ini, sizeof(double));
		    write(pipePaH[numProc][1], &w, sizeof(double));
		    write(pipePaH[numProc][1], &pasos, sizeof(int));

		    wait(&pid); // esperamos al hijo

		    // cerramos las tuberias y leemos los datos obtenidos
		    close(pipeHaP[numProc][1]);
		    close(pipePaH[numProc][0]);

		    read(pipeHaP[numProc][0], &area_calculada, sizeof(double));
		    read(pipeHaP[numProc][0], &ceros, sizeof(int));
		    ceros_totales += ceros; // añadimos las veces que pasamos por el eje 'y'
		    read(pipeHaP[numProc][0], &valor_de_area, sizeof(double));
		    // si el vlor del area es negativa la pasamos a positiva para ir sumando las areas
		    if(valor_de_area == -1.0){
		    	area_calculada *= -1;
		    }
		    areatotal = areatotal + area_calculada;
		}	
		x_ini+=w; // 'avanzamos' al siguiente hijo
	}
	// pintamos los datos pedidos
	printf("%d,%f,%d\n",N_WORKERS,areatotal,ceros_totales);
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
	Este es el metodo que trabaja cuando se envia la señas, pero debido a que
	no funciona correctamente lo he hecho con constantes arriba, pero esta pueso
	el envio y la recepcíon de la señal pese a que esta no funcione
*/
void manejadorSU1(int *ceros){
	ceros++;
}
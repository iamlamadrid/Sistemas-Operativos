#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "constantes.h"

// crear array de posiciones de tablero con fichas
int tablero[TAB];
// crear array de fichas del jugador 1
int blancas[16];
int i;


// crear array de fichas del jugador 2
int negras[16];


// hacer metodo que mueva ficha

int main(){
	for(int i=0; i<16; i++){
		blancas[i] = i;
	}
	for(int i= 48; i<64; i++){
		negras[i] = i;
	}
}

int movimiento(int jugador1[], int jugador2[]){
	int ficha; // ficha que va a mover el jugador (= posicion del array)
	ficha = rand () % (16-(0)+1) + 0; // cogemos una de las fichas aleatoriamente
	int mov; // posicion a la que se va a mover
	mov = rand () % (63-(0)+1) + 0;
	int result = 0;
	int i;
	for(i=0; i<16; i++){
		if(mov = jugador1[i]){
			result = 1;
		}
	}
	for(i=0; i<16; i++){
		if(mov = jugador2[i]){
			result = 2;
		}
	}
	switch(result){
		case 0:
			jugador1[ficha] = mov;
			break;
		case 1:
			break;
		case 2:
			for(int i=0; i<16; i++){
				if(mov = jugador2[i]){
					jugador2[i] = -1;
				}
			}
			break;
	}
}
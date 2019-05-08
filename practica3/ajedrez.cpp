#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <constantes.h>

// crear array de posiciones de tablero con fichas
int tablero[TAB];
// crear array de fichas del jugador 1
int blancas[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15];
// crear array de fichas del jugador 2
int negras[48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63];
// hacer metodo que mueva ficha


int movimiento(int jugador1[], int jugador2[]){
	int ficha; // ficha que va a mover el jugador (= posicion del array)
	ficha = rand () % (16-(0)+1) + 0; // cogemos una de las fichas aleatoriamente
	int mov; // posicion a la que se va a mover
	mov = rand () % (63-(0)+1) + 0;
	int result = comprobar_movimiento(mov);
	switch(result){
		case 0:
			jugador[ficha] = mov;
			break;
		case 1:
			break;
		case 2:
			for(int i=0: i<16; i++){
				if(mov = jugador2[i]){
					jugador2[i] = -1;
				}
			}
			break;
	}
}

int comprobar_movimiento(int num, int jugador1[], int jugador2[]){
	int i;
	for(i=0: i<16; i++){
		if(mov = jugador1[i]){
			return 1;
		}
	}
	for(i=0: i<16; i++){
		if(mov = jugador2[i]){
			return 2;
		}
	}
	return 0;
}
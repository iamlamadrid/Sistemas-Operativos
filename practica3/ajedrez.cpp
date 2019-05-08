#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "constantes.h"

/* 										EXPLICACION:
	Cada jugador tiene un array de 16 posiciones, y cada posicion cuenta como una ficha.
	Dentro de cada posicion se haya un entero que identifica la posicion del tablera donde
	se encuentra dicha ficha.
	Si alguna de las posiciones del array vale -1 quiere decir que esa ficha ha sido comida.
*/

// crear array de posiciones de tablero con fichas
int tablero[TAB];
// creamos array de fichas del jugador 1
int blancas[16];
// creamos array de fichas del jugador 2
int negras[16];
// creamos los jugadores (hilos)
pthread_t player1, player2;

int movimiento();
void empezar_partida();
int comprobar_resultado();

int main(){
	// empezamos la partida colocando las fichas en el tablero
	empezar_partida();

	for( int partidas=0; partidas < 100 ; partidas++ ){
		int control_partida = 0;
		while(control_partida == 0){

		}
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

void empezar_partida(){
	// 'colocamos' las fichas blancas
	for(int i=0; i<16; i++){
		blancas[i] = i;
	}
	// 'colocamos' las fichas negras
	for(int i= 48; i<64; i++){
		negras[i] = i;
	}
}

int comprobar_resultado(int jugador[]){
	for(int i=0; i<16; i++){
		if(jugador[i] != -1){
			return 1;
		}
	}
	return 0;
}
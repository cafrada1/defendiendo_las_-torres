#ifndef __JUEGO_H__
#define __JUEGO_H__

#include <stdbool.h>
#include <string.h>
#include "defendiendo_torres.h"
#include "utiles.h"
#include "animos.h"


#define ENANOS "enanos"
#define ELFOS "elfos"

#define CARACTER_VACIO ' '
#define CARACTER_CAMINO '#'
#define ENTRADA 'E'
#define TORRE 'T'

#define ORCO 'O'
#define ENANO 'G'
#define ELFO 'L'

#define NIVEL_ESTE 1
#define NIVEL_OESTE 2
#define NIVEL_NORTE 3
#define NIVEL_SUR 4

#define MINIMO_CAMINO_SIMPLE 1
#define MAXIMO_CAMINO_SIMPLE 15
#define MINIMO_CAMINO_DOBLE 1
#define MAXIMO_CAMINO_DOBLE 20

#define VELOCIDAD_JUEGO_DEFAULT 1

#define TIEMPO_INICIO 5

typedef struct camino_niveles{

	// caminos[NIVEL DEL JUEGO][NUMERO DEL CAMINO][elementos]
	coordenada_t caminos[CANTIDAD_NIVELES][CANTIDAD_CAMINOS][MAX_LONGITUD_CAMINO];

	// tope_caminos[NIVEL DEL JUEGO][NUMERO DEL CAMINO]
	int tope_caminos[CANTIDAD_NIVELES][CANTIDAD_CAMINOS];

} camino_niveles_t;

/*
* Funcionamiento: abre el archivo de grabacion, ejectura el juego, muestra un mensaje final y asigna el puntaje final. 
*/
void juego_grabando_partida(configuracion_t configuracion,camino_niveles_t caminos,char ruta_grabacion[MAX_RUTA],int *puntaje);

/*
* Funcionamiento: ejectura el juego, muestra un mensaje final y asigna el puntaje final. 
*/
void juego_sin_grabar_partida(configuracion_t configuracion,camino_niveles_t caminos,int *puntaje);

#endif /* __JUEGO_H__ */

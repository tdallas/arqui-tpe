#ifndef BLOBSFRONT_H
#define BLOBSFRONT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <blobsBack.h>

#define LIMPIAPANTALLA clearWorkSpace()

#define MINFILSYCOLS 5
#define MAXFILSYCOLS 10
#define MAXNOMBREARCHIVO 35

#define JUGADORUNO 1
#define JUGADORDOS 2

enum{JUGADORvsJUGADOR=1, JUGADORvsCOMPUTADORA, SALIR};

int iniciarBlobWars();
int menuJuego(tipoPartida *partida);
void cantFilsyCols(tipoPartida *partida);
int generaPartida(tipoPartida *partida);
int jugar(tipoPartida *partida);
void imprimeTablero(const tipoPartida *partida);
int leeIngresado(tipoPartida *partida);
int movimiento(tipoPartida *partida);
void imprimeGanador(const tipoPartida *partida);
void leeNumero(int *numero, int desdeN, int hastaN);
void leeNombre(tipoPartida *partida);
int siOno();

#endif
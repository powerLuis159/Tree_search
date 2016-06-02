#include "stdafx.h"
#include "Ciudad.h"



Ciudad::Ciudad()
{
	id = 0;
	nombre = "default";
	for each (int distancia_a in distancia)
	{
		distancia_a = -1;
	}
}

Ciudad::Ciudad(int identificador)
{
	id = identificador;
	nombre = "";
	for each (int distancia_a in distancia)
	{
		distancia_a = -1;
	}
}

Ciudad::Ciudad(char *nombre_ciudad,int identificador)
{
	id = identificador;
	nombre = nombre_ciudad;
	for (int i = 0; i < N; i++)
	{
		distancia[i] = -1;
	}
}

void Ciudad::asignardistancia(int dist, int ciudad)
{
	if (ciudad >= N)
		return;
	distancia[ciudad] = dist;
}

int Ciudad::obtenerdistancia(int ciudad)
{
	return distancia[ciudad];
}



Ciudad::~Ciudad()
{
}

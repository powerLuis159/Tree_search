// Tree search.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include "Ciudad.h"


struct Ruta
{
	int recorrido[N+1];
	int n_ciudades=0;
	int distancia=0;
	Ruta() { recorrido[0] = 0; }
};
//variabes globales
Ruta mejor_ruta;
Ciudad* Pais[N];
int contar_ciudades(Ruta ruta)
{
	return ruta.n_ciudades;
}

void Añadir_ciudad(Ruta &ruta, Ciudad ciudad)
{
	ruta.distancia += (*Pais[ruta.recorrido[ruta.n_ciudades]]).obtenerdistancia(ciudad.id);
	ruta.n_ciudades++;
	ruta.recorrido[ruta.n_ciudades] = ciudad.id;
}

bool es_mejor_ruta(Ruta ruta)
{
	Añadir_ciudad(ruta, *Pais[0]);
	return ruta.distancia<mejor_ruta.distancia;
}

void actualizar_mejor_ruta(Ruta ruta)
{
	Añadir_ciudad(ruta, *Pais[0]);
	mejor_ruta = ruta;
}

bool factible(Ruta ruta, Ciudad ciudad)
{
	for (int i = 0; i < ruta.n_ciudades ; i++)
	{
		if (ruta.recorrido[i] == ciudad.id)
			return false;
	}

	return (*Pais[ruta.recorrido[ruta.n_ciudades]]).obtenerdistancia(ciudad.id) > 0;
	
}



void Remover_ultima_ciudad(Ruta &ruta)
{
	ruta.distancia -= (*Pais[ruta.recorrido[ruta.n_ciudades - 1]]).obtenerdistancia((*Pais[ruta.recorrido[ruta.n_ciudades]]).id);
	ruta.recorrido[ruta.n_ciudades] = -1;
	ruta.n_ciudades--;
}

void Depth_first_seach(Ruta ruta)
{
	if (contar_ciudades(ruta) == N-1)
	{
		if (es_mejor_ruta(ruta))
			actualizar_mejor_ruta(ruta);
	}
	else 
	{
		for each (Ciudad* ciudad in Pais)
		{
			if (factible(ruta, *ciudad))
			{
				Añadir_ciudad(ruta, *ciudad);
				Depth_first_seach(ruta);
				Remover_ultima_ciudad(ruta);
			}
		}
	}

}

int main()
{
	
	Pais[0] = new Ciudad(0);
	Pais[0]->asignardistancia(1, 1);
	Pais[0]->asignardistancia(3, 2);
	Pais[0]->asignardistancia(8, 3);
	Pais[1] = new Ciudad(1);
	Pais[1]->asignardistancia(5, 0);
	Pais[1]->asignardistancia(2, 2);
	Pais[1]->asignardistancia(6, 3);
	Pais[2] = new Ciudad(2);
	Pais[2]->asignardistancia(1, 0);
	Pais[2]->asignardistancia(18, 1);
	Pais[2]->asignardistancia(10, 3);
	Pais[3] = new Ciudad(3);
	Pais[3]->asignardistancia(7, 0);
	Pais[3]->asignardistancia(4, 1);
	Pais[3]->asignardistancia(12, 2);

	Ruta miruta;
	mejor_ruta.distancia = 1000;
	miruta.recorrido[0] = 0;
	Depth_first_seach(miruta);
    return 0;
}


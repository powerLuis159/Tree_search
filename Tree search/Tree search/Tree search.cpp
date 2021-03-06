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
//vg-norecursivo
std::stack<Ciudad> pila;
std::stack<Ruta> pila_r;
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

void busqueda_no_recursiva()
{
	Ciudad city;
	Ruta ruta_actual;
	for (int c = N-1; c >=0; c--)
	{
		pila.push(*Pais[c]);
	}

	while (!pila.empty()) 
	{
		city=pila.top();
		pila.pop();
		if (city.id == 20)
		{
			Remover_ultima_ciudad(ruta_actual);
		}
		else
		{
			Añadir_ciudad(ruta_actual, city);
			if (contar_ciudades(ruta_actual) == N-1)
			{
				if (es_mejor_ruta(ruta_actual))
					actualizar_mejor_ruta(ruta_actual);
				Remover_ultima_ciudad(ruta_actual);
			}
			else
			{
				pila.push(Ciudad(20));
				for (int nbr = N - 1; nbr >= 1; nbr--)
				{
					if (factible(ruta_actual,*Pais[nbr]))
					{
						pila.push(*Pais[nbr]);
					}
				}
			}
		}
	}
}

void busqueda_no_recursiva_v2()
{
	Ciudad city;
	Ruta ruta_actual;
	pila_r.push(ruta_actual);

	while (!pila_r.empty())
	{
		ruta_actual = pila_r.top();
		pila_r.pop();
		if (contar_ciudades(ruta_actual)==N-1)
		{
			if (es_mejor_ruta(ruta_actual))
			{
				actualizar_mejor_ruta(ruta_actual);
			}
		}
		else
		{
			
			for (int nbr = N-1; nbr >= 1; nbr--)
			{
				if (factible(ruta_actual, *Pais[nbr]))
				{
					Añadir_ciudad(ruta_actual, *Pais[nbr]);
					pila_r.push(ruta_actual);
					Remover_ultima_ciudad(ruta_actual);
				}
			}
		}
	}
}


int main()
{
	/*para cuando N=4
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
	*/

	for (int i = 0; i < N; i++)
	{
		Pais[i] = new Ciudad(i);
		for (int j = 0; j < N; j++)
		{
			Pais[i]->asignardistancia((rand()%50), j);
			if (j == i)
				Pais[i]->asignardistancia(-1, j);
		}
	}


	Ruta miruta;
	mejor_ruta.distancia = 1000;
	miruta.recorrido[0] = 0;
	//Depth_first_seach(miruta);
	busqueda_no_recursiva_v2();
    return 0;
}


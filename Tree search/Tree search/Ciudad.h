#pragma once
#include "stdafx.h"
class Ciudad
{
private:
	
	int distancia[N];
	char* nombre;
public:
	int id;
	Ciudad();
	Ciudad(int);
	Ciudad(char*, int);
	void asignardistancia(int dist, int ciudad);
	int obtenerdistancia(int ciudad);
	~Ciudad();
};


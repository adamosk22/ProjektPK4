#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
#include <iostream>
#include <list>
#include "Potwory.h"
#include "Listy.h"
#include <algorithm>
void Lista::przenies_z_wrogow_do_posiadanych(string nazwa)
{
	list<shared_ptr<Potwor>>::iterator it;
	
	for (it = listaWrogow.begin(); it != listaWrogow.end(); ++it)
	{
		if ((*it)->nazwa == nazwa)
		{
			listaPosiadanych.splice(listaPosiadanych.begin(), listaWrogow, it);
			return;
		}
	}
	cout << "Nie ma takiego potwora";
}


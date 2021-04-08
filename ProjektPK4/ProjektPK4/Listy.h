#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
#include <iostream>
#include <list>
#include "Potwory.h"
class Lista
{
public:
	list< shared_ptr<Potwor>>listaPosiadanych;
	list<shared_ptr<Potwor>>listaWrogow;
	list<shared_ptr<Potwor>>listaLaczonych;
	int liczbaWrogow;

	void przenies_z_wrogow_do_posiadanych(string nazwa);
	shared_ptr<Potwor> oddaj_potwora(string nazwa);
	void przenies_z_laczonych_do_posiadanych(string nazwa);




};
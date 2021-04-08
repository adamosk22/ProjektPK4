#pragma once
#define MAX_NUMBER_OF_ITEMS 3
#include <string>
using namespace std;
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Plik.h"
#include "Rozgrywka.h"
#include "Listy.h"
#include "Potwory.h"
#include <list>
#include <algorithm>
#include <cstdlib> 
#include <ctime> 

class Rozgrywka
{
private:
	int wybrany_przedmiot;
	sf::Font czcionka;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	Lista lista;
	shared_ptr<Potwor> uzywany;
	shared_ptr<Potwor> wrogi;
	sf::Sprite atak_uzyty;
	sf::Sprite atak_wroga_sprite;
public:
	void wyswietlPlansze();
	void stworzMenu(float width, float height, string atak1, string atak2, int liczba_uzyc1, int liczba_uzyc2);
	void rysuj_menu(sf::RenderWindow& window);
	void idz_w_gore();
	void idz_w_dol();
	int otrzymaj_wcisniety() { return wybrany_przedmiot; }
	void zaatakuj(int nr, sf::RenderWindow &window);
	int losuj_bonus();
	
	

};

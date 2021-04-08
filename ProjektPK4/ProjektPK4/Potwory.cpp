#pragma once
#include "Potwory.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
using namespace std;
void Atak::setSprite(std::string source) {
	animacja = loadSpriteAtak(source); 
}

Atak::Atak(string n, int u, int s, char t, string sprite_name)
{
	nazwa = n;
	liczba_uzyc = u;
	sila = s;
	setSprite(sprite_name);
	typ = t;


}
Atak::Atak()
{

}
void Atak::odnow()
{
	liczba_uzyc = 5;
}
void Atak::zaktualizuj(int dodatek)
{
	odnow();
	sila += dodatek;
}
int Atak::uzyj()
{
	if (liczba_uzyc > 0)
	{
		liczba_uzyc--;
		return sila;
	}
	return 0;
}
char Atak::zwroc_typ()
{
	return typ;
}
string Atak::zwroc_nazwe()
{
	return nazwa;
}
int Atak::zwroc_uzycia()
{
	return liczba_uzyc;
}
void Atak::dodaj_param(string n, int u, int s, char t, string sprite_name)
{
	nazwa = n;
	liczba_uzyc = u;
	sila = s;
	typ = t;
	Atak::setSprite(sprite_name);



}

Potwor::Potwor()
{
	nazwa = "blad";
	zycie = 0;
	zycie_max = 0;
	setSprite("water.png");
	sf::IntRect rectSourceSprite(0, 0, 0, 0);
	sprite.setTextureRect(rectSourceSprite);
}
/*Potwor::Potwor(string n, int z, string sprite_name,int x, int y)
{
	nazwa = n;
	zycie = z;
	zycie_max = z;
	setSprite(sprite_name);
	sf::IntRect rectSourceSprite(0, 0, x, y);
	sprite.setTextureRect(rectSourceSprite);

}*/
void Potwor::setSprite(std::string source) {
	sprite = loadSpritePotwor(source); 
}
void Potwor::ulecz(int dodatek)
{
	zycie += dodatek;
	if (zycie > zycie_max)
		zycie = zycie_max;
	odnow_ataki();
}

PotworOgniowy::PotworOgniowy(string n, int z, string sprite_name, int x, int y, string atak1, string atak2, int sila1, int sila2, string nazwa_animacji)
{
	nazwa = n;
	zycie = z;
	zycie_max = z;
	pion = x;
	poziom = y;
	Potwor::setSprite(sprite_name);
	sf::IntRect rectSourceSprite(pion, poziom, 150, 150);
	sprite.setTextureRect(rectSourceSprite);
	dodaj_ataki(atak1, atak2, sila1, sila2, nazwa_animacji);
}
void PotworOgniowy::dodaj_ataki(string atak1, string atak2, int sila1, int sila2, string nazwa_animacji)
{
	ogniowy1.dodaj_param(atak1, 5, sila1, 'o', nazwa_animacji);
	ogniowy2.dodaj_param(atak2, 5, sila2, 'o', nazwa_animacji);
}
void PotworOgniowy::odnow_ataki()
{
	ogniowy1.odnow();
	ogniowy2.odnow();
}
int PotworOgniowy::zaatakuj(int nr)
{
	if (nr == 1)
		return ogniowy1.uzyj();
	if (nr == 2)
		return ogniowy2.uzyj();
}
char PotworOgniowy::zwroc_typ(int nr)
{
	if (nr == 1)
		return ogniowy1.zwroc_typ();
	if (nr == 2)
		return ogniowy2.zwroc_typ();
	
}
string PotworOgniowy::zwroc_nazwe_ataku(int nr)
{
	if (nr == 1)
		return ogniowy1.zwroc_nazwe();
	if (nr == 2)
		return ogniowy2.zwroc_nazwe();
}
int PotworOgniowy::zwroc_liczbe_uzyc(int nr)
{
	if (nr == 1)
		return ogniowy1.zwroc_uzycia();
	if (nr == 2)
		return ogniowy2.zwroc_uzycia();
}
sf::Sprite PotworOgniowy::zwroc_sprite_ataku(int nr)
{
	if (nr == 1)
		return ogniowy1.animacja;
	if (nr == 2)
		return ogniowy2.animacja;
}
PotworTrawiasty::PotworTrawiasty(string n, int z, string sprite_name, int x, int y, string atak1, string atak2, int sila1, int sila2, string nazwa_animacji)
{
	nazwa = n;
	zycie = z;
	zycie_max = z;
	pion = x;
	poziom = y;
	Potwor::setSprite(sprite_name);
	sf::IntRect rectSourceSprite(0, 0, pion, poziom);
	sprite.setTextureRect(rectSourceSprite);
	dodaj_ataki(atak1, atak2, sila1, sila2, nazwa_animacji);
}
void PotworTrawiasty::dodaj_ataki(string atak1, string atak2, int sila1, int sila2, string nazwa_animacji)
{
	trawiasty1.dodaj_param(atak1, 5, sila1, 't', nazwa_animacji);
	trawiasty2.dodaj_param(atak2, 5, sila2, 't', nazwa_animacji);
}
void PotworTrawiasty::odnow_ataki()
{
	trawiasty1.odnow();
	trawiasty2.odnow();
}
int PotworTrawiasty::zaatakuj(int nr)
{
	if (nr == 1)
		return trawiasty1.uzyj();
	if (nr == 2)
		return trawiasty2.uzyj();
}
char PotworTrawiasty::zwroc_typ(int nr)
{
	if (nr == 1)
		return trawiasty1.zwroc_typ();
	if (nr == 2)
		return trawiasty2.zwroc_typ();

}
string PotworTrawiasty::zwroc_nazwe_ataku(int nr)
{
	if (nr == 1)
		return trawiasty1.zwroc_nazwe();
	if (nr == 2)
		return trawiasty2.zwroc_nazwe();
}
int PotworTrawiasty::zwroc_liczbe_uzyc(int nr)
{
	if (nr == 1)
		return trawiasty1.zwroc_uzycia();
	if (nr == 2)
		return trawiasty2.zwroc_uzycia();
}
sf::Sprite PotworTrawiasty::zwroc_sprite_ataku(int nr)
{
	if (nr == 1)
		return trawiasty1.animacja;
	if (nr == 2)
		return trawiasty2.animacja;
}
PotworWodny::PotworWodny(string n, int z, string sprite_name, int x, int y, string atak1, string atak2, int sila1, int sila2, string nazwa_animacji)
{
	nazwa = n;
	zycie = z;
	zycie_max = z;
	pion = x;
	poziom = y;
	Potwor::setSprite(sprite_name);
	sf::IntRect rectSourceSprite(0, 0, pion, poziom);
	sprite.setTextureRect(rectSourceSprite);
	dodaj_ataki(atak1, atak2, sila1, sila2, nazwa_animacji);
}
void PotworWodny::dodaj_ataki(string atak1, string atak2, int sila1, int sila2, string nazwa_animacji)
{
	wodny1.dodaj_param(atak1, 5, sila1, 'w', nazwa_animacji);
	wodny2.dodaj_param(atak2, 5, sila2, 'w', nazwa_animacji);
}
void PotworWodny::odnow_ataki()
{
	wodny1.odnow();
	wodny2.odnow();
}
int PotworWodny::zaatakuj(int nr)
{
	if (nr == 1)
		return wodny1.uzyj();
	if (nr == 2)
		return wodny2.uzyj();
}
char PotworWodny::zwroc_typ(int nr)
{
	if (nr == 1)
		return wodny1.zwroc_typ();
	if (nr == 2)
		return wodny2.zwroc_typ();

}

string PotworWodny::zwroc_nazwe_ataku(int nr)
{
	if (nr == 1)
		return wodny1.zwroc_nazwe();
	if (nr == 2)
		return wodny2.zwroc_nazwe();
}
int PotworWodny::zwroc_liczbe_uzyc(int nr)
{
	if (nr == 1)
		return wodny1.zwroc_uzycia();
	if (nr == 2)
		return wodny2.zwroc_uzycia();
}
sf::Sprite PotworWodny::zwroc_sprite_ataku(int nr)
{
	if (nr == 1)
		return wodny1.animacja;
	if (nr == 2)
		return wodny2.animacja;
}

#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
#include <iostream>
static sf::Sprite loadSpriteAtak(std::string source) {
	static sf::Texture t;
	if (!t.loadFromFile(source)) {
		cerr << "Error: File couldn't be loaded" << std::endl;
	}
	static sf::Sprite s;
	s.setTexture(t);
	return s;
}
static sf::Sprite loadSpritePotwor(std::string source) {
	static sf::Texture t;
	if (!t.loadFromFile(source)) {
		cerr << "Error: File couldn't be loaded" << std::endl;
	}
	static sf::Sprite s;
	s.setTexture(t);
	return s;
}
class Atak
{
	friend class Rozgrywka;
	friend class Potwor;
	string nazwa;
	int liczba_uzyc;
	int sila;
	char typ;
	int x;
	int y;
public:
	
	sf::Sprite animacja;
	Atak(string n, int u, int s, char t, string sprite);
	Atak();
	void odnow();
	void zaktualizuj(int dodatek);
	void setSprite(std::string source);
	int uzyj();
	char zwroc_typ();
	string zwroc_nazwe();
	int zwroc_uzycia();
	void dodaj_param(string n, int u, int s, char t, string sprite_name);
	
};
class Potwor
{
public:
	string nazwa;
	int zycie;
	int zycie_max;
	sf::Sprite sprite;
	//Potwor(string n, int z, string sprite_name, int x, int y);
	int pion;
	int poziom;
	friend class Lista;
	Potwor();
	virtual int zaatakuj(int nr)=0;
	void ulecz(int dodatek);
	virtual void dodaj_ataki(string atak1, string atak2, int sila1, int sila2, string nazwa__animacji) = 0;
	virtual void odnow_ataki()=0;
	virtual char zwroc_typ(int nr) = 0;
	virtual string zwroc_nazwe_ataku(int nr) = 0;
	virtual int zwroc_liczbe_uzyc(int nr) = 0;
	virtual sf::Sprite zwroc_sprite_ataku(int nr)=0;
	void setSprite(string n);
	
};
class PotworOgniowy : public Potwor
{
public:
	Atak ogniowy1;
	Atak ogniowy2;
	PotworOgniowy(string n, int z, string sprite_name, int x, int y,string atak1, string atak2, int sila1, int sila2, string nazwa_animacji);
	virtual void Potwor::dodaj_ataki(string atak1, string atak2, int sila1, int sila2, string nazwa_animacji);
	virtual void Potwor::odnow_ataki();
	virtual int Potwor::zaatakuj(int nr);
	virtual string zwroc_nazwe_ataku(int nr);
	virtual int zwroc_liczbe_uzyc(int nr);
	virtual sf::Sprite zwroc_sprite_ataku(int nr);
	char Potwor::zwroc_typ(int nr);
};
class PotworTrawiasty : public Potwor
{
	Atak trawiasty1;
	Atak trawiasty2;
public:
	PotworTrawiasty(string n, int z, string sprite_name, int x, int y, string atak1, string atak2, int sila1, int sila2, string nazwa_animacji);
	virtual void Potwor::dodaj_ataki(string atak1, string atak2, int sila1, int sila2, string nazwa_animacji);
	virtual void Potwor::odnow_ataki();
	virtual int Potwor::zaatakuj(int nr);
	virtual string zwroc_nazwe_ataku(int nr);
	virtual int zwroc_liczbe_uzyc(int nr);
	virtual sf::Sprite zwroc_sprite_ataku(int nr);
	char Potwor::zwroc_typ(int nr);
	
};
class PotworWodny : public Potwor
{
	Atak wodny1;
	Atak wodny2;
public:
	PotworWodny(string n, int z, string sprite_name, int x, int y, string atak1, string atak2, int sila1, int sila2, string nazwa_animacji);
	virtual void Potwor::dodaj_ataki(string atak1, string atak2, int sila1, int sila2, string nazwa_animacji);
	virtual void Potwor::odnow_ataki();
	virtual int Potwor::zaatakuj(int nr);
	virtual string zwroc_nazwe_ataku(int nr);
	virtual int zwroc_liczbe_uzyc(int nr);
	virtual sf::Sprite zwroc_sprite_ataku(int nr);
	char Potwor::zwroc_typ(int nr);
};
class PotworOgniowoWodny : public PotworOgniowy, public PotworWodny
{

public:
	PotworOgniowoWodny(string n, int z1, int z2, Atak pierwszy, Atak drugi, Atak trzeci, Atak czwarty, sf::Image o);
};
class PotworWodnoTrawiasty : public PotworOgniowy, public PotworWodny
{
	Atak atak3;
	Atak atak4;
public:
	PotworWodnoTrawiasty(string n, int z1, int z2, Atak pierwszy, Atak drugi, Atak trzeci, Atak czwarty, sf::Image o);
};
class PotworTrawiastoWodny : public PotworOgniowy, public PotworWodny
{
	Atak atak3;
	Atak atak4;
public:
	PotworTrawiastoWodny(string n, int z1, int z2, Atak pierwszy, Atak drugi, Atak trzeci, Atak czwarty, sf::Image o);
};

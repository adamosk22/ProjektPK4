#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Plik.h"
#include "Rozgrywka.h"
#include "Listy.h"
#include "Potwory.h"
#include <list>
#include <algorithm>
#include <cstdlib> 
#include <ctime> 

void Rozgrywka::zaatakuj(int nr, sf::RenderWindow &window)
{
	sf::Clock clock;
	int atak = uzywany->zaatakuj(nr);
	switch (uzywany->zwroc_typ(nr))
	{
	case 'o':
		switch (wrogi->zwroc_typ(nr))
		{
		case 'o':
			break;
		case 'w':
			atak -= (0.2 * atak);
			break;
		case 't':
			atak += (0.2 * atak);
			break;

		}
		break;
		
	case 'w':
		switch (wrogi->zwroc_typ(nr))
		{
		case 'o':
			atak += (0.2 * atak);
			break;
		case 'w':
			break;
		case 't':
			atak -= (0.2 * atak);
			break;

		}
		break;
		
	case 't':
		switch (wrogi->zwroc_typ(nr))
		{
		case 'o':
			atak -= (0.2 * atak);
			break;
		case 'w':
			atak += (0.2 * atak);
			break;
		case 't':
			break;

		}
		break;
	}
	if (losuj_bonus() == 1)
		atak += (0.5 * atak);
	if (losuj_bonus() == 2)
		atak = 0;
	atak_uzyty = uzywany->zwroc_sprite_ataku(nr);
	sf::IntRect rectSourceSprite(0, 0, 160, 190);
	atak_uzyty.setTextureRect(rectSourceSprite);
	
		
	while (window.isOpen())
	{
		if (clock.getElapsedTime().asSeconds() > 1.0f) {
			if (rectSourceSprite.left == 600)
			{
				rectSourceSprite.left = 0;
				rectSourceSprite.top += 190;
				break;
			}
			else
			{
				rectSourceSprite.left += 200;
			}

			atak_uzyty.setTextureRect(rectSourceSprite);
			clock.restart();
		}
	}

	

	wrogi->zycie -= atak;
	if (wrogi->zycie <= 0)
		wrogi->zycie = 0;
	
	cout << "Wrog ma " << wrogi->zycie << " na " << wrogi->zycie_max<<endl;
	if (wrogi->zycie == 0)
	{
		lista.przenies_z_wrogow_do_posiadanych(wrogi->nazwa);
		if (!lista.listaWrogow.empty())
			wrogi = *lista.listaWrogow.begin();
		else
			cout << "Zwyciestwo";
	}
	else
	{
		srand((unsigned)time(0));
		int i;
		i = (rand() % 2) + 1;
		int atak_wroga = wrogi->zaatakuj(i);
		switch (uzywany->zwroc_typ(i))
		{
		case 'o':
			switch (uzywany->zwroc_typ(nr))
			{
			case 'o':
				break;
			case 'w':
				atak_wroga -= (0.2 * atak);
				break;
			case 't':
				atak_wroga += (0.2 * atak);
				break;

			}
			break;
		case 'w':
			switch (uzywany->zwroc_typ(nr))
			{
			case 'o':
				atak_wroga += (0.2 * atak);
				break;
			case 'w':
				break;
			case 't':
				atak_wroga -= (0.2 * atak);
				break;

			}
			break;
		case 't':
			switch (uzywany->zwroc_typ(nr))
			{
			case 'o':
				atak_wroga -= (0.2 * atak);
				break;
			case 'w':
				atak_wroga += (0.2 * atak);
				break;
			case 't':
				break;

			}
			break;
		}
		if (losuj_bonus() == 1)
			atak_wroga += (0.5 * atak);
		if (losuj_bonus() == 2)
			atak_wroga = 0;
		atak_wroga_sprite = wrogi->zwroc_sprite_ataku(nr);
		sf::IntRect rectSourceSprite2(0, 0, 160, 190);
		atak_wroga_sprite.setTextureRect(rectSourceSprite2);
		sf::Event event;
		while (window.isOpen())
		{
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::EventType::Closed)
					window.close();
			}
			if (clock.getElapsedTime().asSeconds() > 1.0f) {
				if (rectSourceSprite2.left == 600)
				{
					break;
				}
				else
				{
					rectSourceSprite2.left += 200;
				}
				atak_wroga_sprite.setTextureRect(rectSourceSprite2);
				window.draw(atak_wroga_sprite);
				clock.restart();
			}
		}
		uzywany->zycie -= atak;
		if (uzywany->zycie <= 0)
			uzywany->zycie = 0;
		
		cout << "Masz " << uzywany->zycie << " na " << uzywany->zycie_max << endl;
		if (uzywany->zycie <= 0)
		{
			list<shared_ptr<Potwor>>::iterator it;

			for (it = lista.listaPosiadanych.begin(); it != lista.listaPosiadanych.end(); ++it)
			{
				if ((*it)->nazwa == uzywany->nazwa)
				{
					lista.listaPosiadanych.erase(it);
				}
			}
			if (!lista.listaPosiadanych.empty())
				uzywany = *lista.listaPosiadanych.begin();
			else
				cout << "Porazka";
		}
	}

	
	




}
int Rozgrywka::losuj_bonus()
{
	srand((unsigned)time(0));
	int i;
	i = (rand() % 10) + 1;
	if (i == 5)
		return 1;
	else if (i == 8)
		return 2;
	else
		return 0;
}
void Rozgrywka::wyswietlPlansze()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "MojeOkno");

	


	shared_ptr<Potwor> p = make_unique<PotworOgniowy>("a", 20, "water.png", 150, 150, "ogniowy cios", "sila ognia", 10, 15, "fireattack.png");
	
	lista.listaWrogow.push_back(p);
	shared_ptr<Potwor> r = make_unique<PotworTrawiasty>("b", 20, "water.png", 150, 150, "ogniowy cios", "sila ognia", 10, 15, "fireattack.png");
	lista.listaWrogow.push_back(r);
	shared_ptr<Potwor> s = make_unique<PotworOgniowy>("c", 20, "water.png", 150, 150, "ogniowy cios", "sila ognia", 10, 15, "fireattack.png");
	lista.listaPosiadanych.push_back(s);
	shared_ptr<Potwor> t = make_unique<PotworOgniowy>("d", 20, "water.png", 150, 150, "ogniowy cios", "sila ognia", 10, 15, "fireattack.png");
	lista.listaPosiadanych.push_back(t);
	wrogi = *lista.listaWrogow.begin();
	uzywany = *lista.listaWrogow.begin();

	



	
	sf::Event event;

	sf::IntRect rectSourceSprite(0, 0, 150, 150);
	sf::IntRect rectSourceSprite2(0, 0, 160, 190);

	sf::Sprite enemySprite = wrogi->sprite;
	sf::Sprite friendSprite = uzywany->sprite;
	
	//Atak atak1("atak ognia", 2, 4, "fireattack.png");
	
	friendSprite.setPosition(0.f, 0.f);
	enemySprite.setPosition(400.f, 0.f);
	//sf::Clock clock;
	stworzMenu(600, 600, uzywany->zwroc_nazwe_ataku(1), uzywany->zwroc_nazwe_ataku(2),uzywany->zwroc_liczbe_uzyc(1), uzywany->zwroc_liczbe_uzyc(2));
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::EventType::Closed)
				window.close();
			
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					idz_w_gore();
					break;

				case sf::Keyboard::Down:
					idz_w_dol();
					break;

				case sf::Keyboard::Return:
					switch (otrzymaj_wcisniety())
					{
					case 0:
						std::cout << "Uzyto ataku 1" << std::endl;
						zaatakuj(1, window);
						break;
					case 1:
						std::cout << "Uzyto ataku 2" << std::endl;
						zaatakuj(2, window);
						break;
					case 2:
						std::cout << "Zmieniono potwora" << std::endl;

						break;
					}

					break;
				}

				break;
			case sf::Event::Closed:
				window.close();

				break;
			}

		}
		/*if (clock.getElapsedTime().asSeconds() > 1.0f) {
			if (rectSourceSprite.left == 600)
			{
				rectSourceSprite2.left = 0;
				rectSourceSprite2.top += 190;
			}
			else
			{
				rectSourceSprite2.left += 200;
			}
			
			
			clock.restart();
		}*/
		








		window.clear(sf::Color::Blue);
		for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
		{
			window.draw(menu[i]);
		}
		
		window.draw(enemySprite);
		window.draw(friendSprite);
		window.draw(atak_uzyty);
		window.draw(atak_wroga_sprite);
		window.display();
	}
	
}



void Rozgrywka::stworzMenu(float width, float height, string atak1, string atak2, int liczba_uzyc1, int liczba_uzyc2)
{
	if (!czcionka.loadFromFile("Aerwyna.ttf"))
	{
		cout << "Plik czcionki nie otwiera siê.";
	}
	string napis1 = atak1 + " " + to_string(liczba_uzyc1) + "/5";
	string napis2 = atak2 + " " + to_string(liczba_uzyc2) + "/5";

	menu[0].setFont(czcionka);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString(napis1);
	menu[0].setPosition(sf::Vector2f(width / 6, 300 + height / (3 * (MAX_NUMBER_OF_ITEMS + 1))*1));

	menu[1].setFont(czcionka);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString(napis2);
	menu[1].setPosition(sf::Vector2f(width / 6,  300 + height / (3 * (MAX_NUMBER_OF_ITEMS + 1))*2));
	

	menu[2].setFont(czcionka);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Zmieñ potwora");
	menu[2].setPosition(sf::Vector2f(width / 6, 300 + height / (3 * (MAX_NUMBER_OF_ITEMS + 1))*3));

	wybrany_przedmiot = 0;
}




void Rozgrywka::rysuj_menu(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Rozgrywka::idz_w_gore()
{
	if (wybrany_przedmiot - 1 >= 0)
	{
		menu[wybrany_przedmiot].setFillColor(sf::Color::White);
		wybrany_przedmiot--;
		menu[wybrany_przedmiot].setFillColor(sf::Color::Red);
	}
}

void Rozgrywka::idz_w_dol()
{
	if (wybrany_przedmiot + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[wybrany_przedmiot].setFillColor(sf::Color::White);
		wybrany_przedmiot++;
		menu[wybrany_przedmiot].setFillColor(sf::Color::Red);
	}
}
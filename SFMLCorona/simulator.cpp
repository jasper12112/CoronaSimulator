#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>


#include "Person.h"
#include "settings.h"
#include "simulator.h"

simulator::simulator(sf::RenderWindow* window)
{
	this->window = window;
	for (int k = 0; k < TOTAL_POPULAR_PLACES; k++)
	{
		populairPlaces.push_back(popularplace(sf::Color(110, 110, 110), 14, 16, 5));
	}
}

int randomFactor(int min, int max)
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(min, max); // define the range

	return distr(gen);
}

void simulator::SimulateP(int i, int &totalInfactions, int &totalVulnerable, int &totalImmune, int &totalDead, sf::RenderWindow* window, Person myPeople[])
{
	if (randomFactor(0, 10) > CHANGE_GO_PLACE)
	{
		sf::Vector2f loc = getPPLoc();
		myPeople[i].Move(loc, true);
	}else
	{
		myPeople[i].Move(sf::Vector2f(0, 0), false);
	}
	
	myPeople[i].ProgressDisease();

	switch (myPeople[i].state)
	{
	case Infected:

		myPeople[i].Draw(window, sf::Color::Green);
		for (int j = 0; j < TOTAL_PEOPLE; j++) { myPeople[i].Infect(myPeople[j]); }
		totalInfactions++;
		break;
	case Vulnerable:
		myPeople[i].Draw(window, sf::Color::White);
		totalVulnerable++;
		break;
	case Dead:
		totalDead++;
		myPeople[i].Draw(window, sf::Color::Red);
		break;
	case Immume:
		totalImmune++;
		myPeople[i].Draw(window, sf::Color::Blue);
		break;
	}
}

void simulator::BackFromVacation(int totalInfactions, Person myPeople[])
{
	if (totalInfactions <= 0)
	{
		
		int deadPeopleCounted = 0;
		for (int j = 0; j < TOTAL_PEOPLE; j++)
		{
			if (myPeople[j].state == Dead)
			{
				deadPeopleCounted++;
				myPeople[j].state = Infected;
				if (randomFactor(0, 10) > 5)
				{
					int randX = randomFactor(0, 600);
					myPeople[j].body.setPosition(randX, 0);
					myPeople[j].LocationX = randX;
					myPeople[j].LocationY = 0;
				}
				else
				{
					int randY = randomFactor(0, pFieldY);
					myPeople[j].body.setPosition(600, randY);
					myPeople[j].LocationX = 600;
					myPeople[j].LocationY = randY;
				}
			}
			if (deadPeopleCounted >= 5)
			{
				break;
			}
		}
	}
}

void simulator::SimulatePlaces()
{
	for(int i = 0; i < populairPlaces.size(); i++)
	{
		populairPlaces[i].draw(window);
	}
}

sf::Vector2f simulator::getPPLoc()
{
	return populairPlaces[randomFactor(0, populairPlaces.size() - 1)].GetLocation();
}

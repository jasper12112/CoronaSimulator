#pragma once
#include "Person.h"
#include "popularplace.h"

class simulator
{
	
public:
	simulator(sf::RenderWindow* window);

	sf::RenderWindow* window;
	
	std::vector<popularplace> populairPlaces;
	
	void SimulateP(int i, int& totalInfactions, int& totalVulnerable, int& totalImmune, int& totalDead, sf::RenderWindow* window, Person myPeople[]);

	void BackFromVacation(int totalInfactions, Person myPeople[]);

	void SimulatePlaces();

	void RandomInfect(Person myPeople[]);

	sf::Vector2f getPPLoc();
};


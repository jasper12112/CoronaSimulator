#include "popularplace.h"

#include <random>

int randomNumber(int min, int max)
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(min, max); // define the range
	
	return distr(gen);
}

popularplace::popularplace(sf::Color color, int sizeX, int sizeY, int maxPeople)
{
	body.setFillColor(color);
	body.setSize(sf::Vector2f(sizeX, sizeY));
	Location = new sf::Vector2f(randomNumber(0, PFieldX), randomNumber(0, pFieldY));
	
	body.setPosition(Location->x - (sizeX / 2), Location->y - (sizeY / 2));
	this->SizeX = sizeX;
	this->SizeY = sizeY;
	this->maxPeople = maxPeople;
}

void popularplace::draw(sf::RenderWindow* window)
{
	window->draw(body);
}

bool popularplace::PlaceIsAvaible()
{
	return currentPeople < maxPeople;
}

void popularplace::PlaceEnter()
{
	currentPeople++;
}

void popularplace::PlaceGo()
{
	currentPeople--;
}

sf::Vector2f popularplace::GetLocation()
{
	return body.getPosition();
}

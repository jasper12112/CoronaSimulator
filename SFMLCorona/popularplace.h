#pragma once
#include <SFML/Graphics.hpp>
#include "settings.h"

class popularplace
{
	public:
		popularplace(sf::Color color, int sizeX, int sizeY, int maxPeople);
		
		sf::RectangleShape body;

		sf::Vector2f* Location;

		int maxPeople;
		int currentPeople;
	
		int SizeX;
		int SizeY;

		void draw(sf::RenderWindow* window);

		bool PlaceIsAvaible();

		void PlaceEnter();

		void PlaceGo();

		sf::Vector2f GetLocation();
};


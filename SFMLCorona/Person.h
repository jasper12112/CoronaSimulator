#pragma once
#include <SFML/Graphics.hpp>

#include "popularplace.h"
#include "settings.h"

class popularplace;

enum PersonState {Vulnerable, Immume, Infected, Dead};

class Person
{
	public:
		Person();

		float LocationX, LocationY;

		int stayTime = STAY_TIME;
		int CurrentStayTime;
		
		int InfectedTime = INFECTION_TIME;
		int CurrentedInfectedTime;

		int ImmuneTime = IMMUNE_TIME;
		int CurrentImmuneTime;
		

		sf::Vector2f HomeLocation;
		
		void Draw(sf::RenderWindow* window, sf::Color color);

		float GetDistance(double x1, double x2, double y1, double y2);
		
		void Infect(Person &otherPerson);

		void Move(sf::Vector2f Loc, bool succes);

		void ProgressDisease();

		void SetState(PersonState newState);

		float speed;

		bool inLocation;

		PersonState state;

		sf::RectangleShape body;

		sf::CircleShape infectionRadius = sf::CircleShape(INFECTION_RADIUS);
};


#include "Person.h"

#include <iostream>

#include "settings.h"
#include <random>

#include "popularplace.h"

int randomLocationPerson(int min, int max)
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(min, max); // define the range

	return distr(gen);
}

Person::Person()
{
	LocationX = (float)randomLocationPerson(1, PFieldX - 1);
	LocationY = (float)randomLocationPerson(1, pFieldY - 1);

	HomeLocation = sf::Vector2f(randomLocationPerson(1, PFieldX - 1), randomLocationPerson(1, pFieldY - 1));

	CurrentStayTime = 0;
	CurrentedInfectedTime = 0;
	CurrentImmuneTime = 0;
	
	body.setSize(sf::Vector2f(PersonSize, PersonSize));
	body.setPosition(LocationX, LocationY);
	
	inLocation = false;
	
	//infectionRadius.setScale(INFECTION_RADIUS -2, INFECTION_RADIUS -2);
	infectionRadius.setFillColor(sf::Color::Transparent);
	infectionRadius.setOutlineThickness(.3f);
	infectionRadius.setOutlineColor(sf::Color::Green);

	state = Vulnerable;

	speed = (float)PLAYER_SPEED;
}

void Person::Draw(sf::RenderWindow* window, sf::Color color)
{
	body.setFillColor(color);
	window->draw(body);
	
	if(state == Infected && SHOW_RADIUS)
	{
		window->draw(infectionRadius);
	}
}

float Person::GetDistance(double x1, double x2, double y1, double y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}

void Person::Infect(Person& otherPerson)
{
	if (otherPerson.state != Vulnerable) return;

	float distance = GetDistance(LocationX, otherPerson.LocationX, LocationY, otherPerson.LocationY);
	
	if(distance <= INFECTION_RADIUS)
	{
		if(randomLocationPerson(0, 100) > INFECTION_CHANCE)
		{
			otherPerson.CurrentImmuneTime = 0;
			otherPerson.CurrentedInfectedTime = 0;
			otherPerson.SetState(Infected);
		}
	}
	
}

void Person::ProgressDisease()
{
	if(state == Infected)
	{
		CurrentedInfectedTime++;
		if(CurrentedInfectedTime >= InfectedTime)
		{
			if(randomLocationPerson(0, 100) >= CHANCE_TO_DIE)
			{
				SetState(Dead);
				return;
			}
			SetState(Immume);
			return;
		}
	}
	else if(state == Immume)
	{
		CurrentImmuneTime++;
		if (CurrentImmuneTime >= ImmuneTime)
		{
			SetState(Vulnerable);
		}
	}
}

void Person::SetState(PersonState newState)
{
	CurrentedInfectedTime = 0;
	CurrentImmuneTime = 0;
	state = newState;
}

void Person::Move(sf::Vector2f Loc, bool succes)
{
	if (state == Dead) return;
	
	if(GetDistance(LocationX, HomeLocation.x, LocationY, HomeLocation.y) <= 2.5f && CurrentStayTime < stayTime)
	{
		CurrentStayTime++;
	}
	else if(CurrentStayTime >= stayTime)
	{
		CurrentStayTime = 0;

		inLocation = false;
		if(succes)
		{
			inLocation = true;
			HomeLocation = Loc;
		}else
		{
			inLocation = false;
			HomeLocation = sf::Vector2f(randomLocationPerson(1, PFieldX - 1), randomLocationPerson(1, pFieldY - 1));
		}
	}
	else
	{
		//Move to home
		if(LocationX < HomeLocation.x)
		{
			LocationX = LocationX + speed;
		}
		else
		{
			LocationX = LocationX - speed;
		}

		if(LocationY < HomeLocation.y)
		{
			LocationY = LocationY + speed;
		}
		else
		{
			LocationY = LocationY - speed;
		}

		body.setPosition(LocationX, LocationY);
		infectionRadius.setPosition(body.getPosition().x - (INFECTION_RADIUS / 2 + 2), body.getPosition().y - (INFECTION_RADIUS / 2 + 2));
	}
}

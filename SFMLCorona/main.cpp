#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

#include "graph.h"
#include "simulator.h"
#include "Person.h"
#pragma once
#include "settings.h"

int randomLocation(int min, int max)
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(min, max); // define the range
	
	return distr(gen);
}


int main()
{
	//Total states people
	int totalInfactions = 0;
	int totalVulnerable = TOTAL_PEOPLE - 5;
	int totalImmune = 0;
	int totalDead = 0;

	//Initialisers
	int Current_Sim_Hours = 0;
	int startInfected = 0;
	
	sf::RenderWindow* window;
	window = new sf::RenderWindow(sf::VideoMode(1280, pFieldY), "CoronaSimulator", sf::Style::Close | sf::Style::Titlebar);
	window->setFramerateLimit(FRAME_RATE_LIMIT);

	int currentFrameRate = FRAME_RATE_LIMIT;
	int currentFrameRateIndex = 2;

	graph* curveInfected = new graph(0, 1280, 25);
	graph* curveDead = new graph(0, 1280,  25);
	graph* curveVulnerable = new graph(0, 1280, 25);
	graph* curveImmune = new graph(0, 1280, 25);

	simulator* sim = new simulator(window);

	Person myPeople[TOTAL_PEOPLE];

	while(window->isOpen())
	{
		//while (Current_Sim_Hours < SIM_HOURS)
		//while (totalVulnerable > 0 && playLoop)
		while(true)
		{
			sf::Event evnt;

			while (window->pollEvent(evnt))
			{
				switch (evnt.type)
				{
				case sf::Event::Closed:
					window->close();
					break;
				case sf::Event::KeyPressed:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
					{
						sim->RandomInfect(myPeople);
					}
					else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
					{
						currentFrameRate = currentFrameRate + 10;
						window->setFramerateLimit(currentFrameRate);
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
					{
						currentFrameRate = currentFrameRate - 10;
						window->setFramerateLimit(currentFrameRate);
					}
					break;
				}
			}

			//if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
			//{
			//	printf("ULTRA TRUE");
			//	sim->RandomInfect(myPeople);
			//}

			window->clear(sf::Color::Black);
			sim->SimulatePlaces();
			
			totalInfactions = 0;
			totalVulnerable = 0;
			totalDead = 0;
			totalImmune = 0;

			for (int i = 0; i < TOTAL_PEOPLE; i++)
			{
				if (startInfected < TOTAL_START_INFECTED)
				{
					myPeople[i].SetState(Infected);
					startInfected++;
				}

				sim->SimulateP(i, totalInfactions, totalVulnerable, totalImmune, totalDead, window, myPeople);
			}

			//sim->BackFromVacation(totalInfactions, myPeople);
			
			curveInfected->Draw(window);
			curveDead->Draw(window);
			curveVulnerable->Draw(window);
			curveImmune->Draw(window);
			window->display();

			Current_Sim_Hours++;

			if(Current_Sim_Hours % 16 == 0)
			{
				curveInfected->UpdateGraph(totalInfactions, sf::Color::Green);
				curveDead->UpdateGraph(totalDead, sf::Color::Red);
				curveVulnerable->UpdateGraph(totalVulnerable, sf::Color::White);
				curveImmune->UpdateGraph(totalImmune, sf::Color::Blue);
			}
		}
	}
	
    return 0;
}
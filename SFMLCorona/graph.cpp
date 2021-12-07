#include "graph.h"


#include <iostream>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>

#pragma once
#include "settings.h"

graph::graph(int xStart, int limitX, int additional)
{
	graphx = xStart;
	curve.clear();
	this->limitX = limitX;
	this->additional = additional;
}


void graph::Draw(sf::RenderWindow* window)
{
	window->draw(curve);
}

void graph::UpdateGraph(int total, sf::Color color)
{
	if (graphx + PFieldX + additional >= limitX)
	{
		curve.clear();
		graphx = 0;
	}
	
	curve.append(sf::Vertex(sf::Vector2f(graphx + PFieldX + additional, (total * -1) + (pFieldY + 4 / 2) + -5)));
	curve[graphx].color = color;
	graphx++;
}

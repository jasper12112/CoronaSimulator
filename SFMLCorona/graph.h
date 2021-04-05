#pragma once
#include <deque>
#include <SFML/Graphics/VertexArray.hpp>

namespace sf {
	class RenderWindow;
	class Color;
	class VertexArray;
}

class graph
{
public:

	graph(int xStart, int limitX, int additional);

	sf::VertexArray curve = sf::VertexArray(sf::PrimitiveType::LineStrip, 100);

	sf::PrimitiveType m_primitiveType;
	std::deque<sf::Vertex> m_vertices;
	
	int graphx;
	int limitX;
	int additional;

	void Draw(sf::RenderWindow* window);

	void UpdateGraph(int total, sf::Color color);
};


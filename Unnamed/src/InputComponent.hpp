#pragma once
#include <iostream>
#include <SFML/Graphics/Vertex.hpp>

class InputComponent
{
public:
	virtual const sf::Vector2f& GetDirection() = 0;
	virtual void Move(sf::Vector2f direction) = 0;
	virtual void Shoot(bool isShooting) = 0;
	virtual void ClearDirection() = 0;
};

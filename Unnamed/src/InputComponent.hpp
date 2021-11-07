#pragma once
#include <iostream>
#include <SFML/System/Vector2.hpp>

class InputComponent
{
public:
	virtual sf::Vector2f GetDirection() = 0;
	virtual void Move(sf::Vector2f direction) = 0;
	virtual void ClearDirection() = 0;
};

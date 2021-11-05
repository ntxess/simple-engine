#pragma once
#include <SFML/System/Vector2.hpp>

class InputComponent
{
public:
	virtual void Move(sf::Vector2f direction) = 0;
	virtual sf::Vector2f GetDirection() = 0;
	virtual void ClearDirection() = 0;
};

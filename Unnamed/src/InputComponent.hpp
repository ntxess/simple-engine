#pragma once
#include <SFML/Graphics.hpp>

class InputComponent
{
public:
	virtual sf::Vector2f GetDirection() const = 0;
	virtual void Update(const sf::Event& event) = 0;
};

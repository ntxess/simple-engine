#pragma once
#include "InputComponent.hpp"

class PlayerInput : public InputComponent
{
public:
	sf::Vector2f _direction;

	PlayerInput();
	~PlayerInput();
	sf::Vector2f GetDirection();
	void Move(sf::Vector2f direction);
	void ClearDirection();
};
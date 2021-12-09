#pragma once
#include "InputComponent.hpp"

class PlayerInput : public InputComponent
{
private:
	sf::Vector2f _direction;

public:
	PlayerInput();
	~PlayerInput();
	const sf::Vector2f& GetDirection();
	void Move(sf::Vector2f direction);
	void Shoot(bool isShooting);
	void ClearDirection();
};
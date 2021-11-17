#pragma once
#include "InputComponent.hpp"

class CPUInput : public InputComponent
{
private:
	sf::Vector2f _direction;
	sf::Vector2f _previousD;

public:
	CPUInput();
	~CPUInput();
	const sf::Vector2f& GetDirection();
	void Move(sf::Vector2f direction);
	void ClearDirection();
};
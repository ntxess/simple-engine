#pragma once
#include <iostream>
#include <SFML/Graphics/Vertex.hpp>

class InputComponent
{
private:
	sf::Vector2f _direction;

public:
	InputComponent();
	~InputComponent();
	const sf::Vector2f& GetDirection();
	void Move(sf::Vector2f direction);
	void Update(float velocity);
	void ClearDirection();
};

#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include "InputComponent.hpp"

class PhysicsComponent
{
private:
	InputComponent _input;
	bool _isTouched;
	float _velocity;

public:
	PhysicsComponent();
	void Update(sf::Sprite& sprite, sf::Vector2f direction, float deltaTime);
};
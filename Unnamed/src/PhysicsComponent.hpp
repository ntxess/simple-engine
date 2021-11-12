#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Vertex.hpp>

class PhysicsComponent
{
public:
	virtual void Move(sf::Sprite& sprite, sf::Vector2f direction, float deltaTime) = 0;
	virtual void Update(sf::Sprite& sprite, sf::Vector2f direction, float deltaTime) = 0;
};
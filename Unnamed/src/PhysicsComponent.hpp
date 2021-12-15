#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Vertex.hpp>

class PhysicsComponent
{
public:
	PhysicsComponent();
	void Update(sf::Sprite& sprite, sf::Vector2f direction, float deltaTime);
};
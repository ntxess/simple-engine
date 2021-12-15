#pragma once
#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <Thor/Animations.hpp>

class GraphicsComponent
{
public:
	virtual void EventReceiver(sf::Vector2f direction) = 0;
	virtual void Update(sf::Sprite& sprite, sf::Vector2f direction, float deltaTime) = 0;
};
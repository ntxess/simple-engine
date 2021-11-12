#pragma once
#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <Thor/Animations.hpp>

class GraphicsComponent
{
public:
	virtual thor::Animator<sf::Sprite, std::string>& GetAnimator() = 0;
	virtual void EventReceiver(sf::Vector2f direction) = 0;
	virtual void Update(sf::Vector2f direction, float deltaTime) = 0;
};
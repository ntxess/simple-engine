#pragma once
#include "GraphicsComponent.hpp"

class ShipAnimation : public GraphicsComponent
{
private:
	thor::Animator<sf::Sprite, std::string> _animator;

public:
	ShipAnimation();
	~ShipAnimation();
	void EventReceiver(sf::Vector2f direction);
	void Update(sf::Sprite& sprite, sf::Vector2f direction, float deltaTime);
};
#pragma once
#include "GraphicsComponent.hpp"

class Sprite : public GraphicsComponent
{
private:
	thor::Animator<sf::Sprite, std::string> _animator;

public:
	Sprite();
	~Sprite();
	thor::Animator<sf::Sprite, std::string>& GetAnimator();
	void EventReceiver(sf::Vector2f direction);
	void Update(sf::Vector2f direction, float deltaTime);
};
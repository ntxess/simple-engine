#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>
#include <Thor/Animations.hpp>

typedef std::unique_ptr<sf::RenderWindow> RenderWindowRef;

class GraphicsComponent
{
public:
	virtual sf::Sprite& GetSprite() = 0;
	virtual thor::Animator<sf::Sprite, std::string>& GetAnimator() = 0;
	virtual void Move(sf::Vector2f direction, float velocity, float deltaTime) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Update(sf::Vector2f direction, float velocity, float deltaTime) = 0;
	virtual void Render(RenderWindowRef& rw, float interpolation) = 0;
};
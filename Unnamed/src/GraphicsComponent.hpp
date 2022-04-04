#pragma once
#include <SFML/Graphics.hpp>
#include <Thor/Animations.hpp>

#include "GameObject.hpp"

class GameObject;

typedef std::unique_ptr<sf::RenderWindow> RenderWindowRef;

class GraphicsComponent
{
public:
	virtual sf::Sprite& GetSprite() = 0;
	virtual void Animator(const GameObject& object) = 0;
	virtual void Render(const RenderWindowRef& rw, const float& deltaTime, const float& interpolation) = 0;
};
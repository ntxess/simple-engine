#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
public:
	Entity() {}
	virtual ~Entity() {}
	virtual void Update() = 0;
	virtual void Render(sf::RenderTarget* rt, double interpolation) = 0;
};
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Thor/Animations.hpp>

class GraphicsComponent
{
public:
	virtual sf::Sprite& GetSprite() = 0;
	virtual void Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& interpolation) = 0;
};
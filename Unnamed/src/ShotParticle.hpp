#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>

class ShotParticle
{
public:
	ShotParticle();
	ShotParticle(thor::ResourceHolder<sf::Texture, std::string>& holder, sf::Vector2f position);
	~ShotParticle();
};
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>
#include "GameObject.hpp"

class ShotParticle : public GameObject
{
public:
	ShotParticle();
	ShotParticle(thor::ResourceHolder<sf::Texture, std::string>& holder, sf::Vector2f position);
	~ShotParticle();
};
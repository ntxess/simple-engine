#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Entity.hpp"

class GameActor : public Entity
{
public:
	GameActor();
	~GameActor();
	virtual void Update();
	virtual void Render(sf::RenderTarget* rt, double interpolation);
};
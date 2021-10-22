#pragma once
#include <SFML/Graphics.hpp>

class State
{
public:
	virtual void Init() = 0;
	virtual void ProcessInput() = 0;
	virtual void Update(double deltaTime) = 0;
	virtual void Render(sf::RenderWindow* rt, double interpolation) = 0;
	virtual void Pause() {};
	virtual void Resume() {};
};
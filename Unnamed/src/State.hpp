#pragma once
#include <SFML/Graphics.hpp>

class State
{
public:
	virtual void Init() = 0;
	virtual void ProcessInput() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(sf::RenderWindow &rw, float interpolation) = 0;
	virtual void Pause() {};
	virtual void Resume() {};
};
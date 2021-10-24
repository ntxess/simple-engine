#pragma once
#include <SFML/Graphics.hpp>

typedef std::unique_ptr<sf::RenderWindow> RenderWindowRef;

class State
{
public:
	virtual void Init() = 0;
	virtual void ProcessInput() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(RenderWindowRef& rw, float interpolation) = 0;
	virtual void Pause() {};
	virtual void Resume() {};
};
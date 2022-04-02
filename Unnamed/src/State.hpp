#pragma once
#include <SFML/Graphics.hpp>
#include <Thor/Animations.hpp>

typedef std::unique_ptr<sf::RenderWindow> RenderWindowRef;

class State
{
public:
	virtual void Init() = 0;
	virtual void ProcessEvent(sf::Event event) = 0;
	virtual void ProcessInput(sf::Event event) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(RenderWindowRef& rw, float deltaTime, float interpolation) = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
};
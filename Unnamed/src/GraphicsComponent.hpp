#pragma once

class GraphicsComponent
{
public:
	virtual ~GraphicsComponent() {}
	virtual void SetScale(const sf::Vector2f scale) = 0;
	virtual void SetPosition(const sf::Vector2f pos) = 0;
	virtual void Update(double deltaTime) = 0;
	virtual void Render(sf::RenderTarget* rt, double interpolation) = 0;
};
#pragma once

class GraphicsComponent
{
public:
	virtual ~GraphicsComponent() {}
	virtual void Update() = 0;
	virtual void Render(sf::RenderTarget* rt, double interpolation) = 0;
};
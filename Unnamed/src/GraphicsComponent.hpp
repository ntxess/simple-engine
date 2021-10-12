#pragma once

class GraphicsComponent
{
public:
	virtual ~GraphicsComponent() {}
	virtual void Render(sf::RenderTarget* rt, double interpolation) = 0;
};
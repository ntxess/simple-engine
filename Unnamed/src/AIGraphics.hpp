#pragma once
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>
#include <Thor/Animations.hpp>

#include "GraphicsComponent.hpp"

class AIGraphics : public GraphicsComponent
{
private:
	sf::Sprite _sprite;

public:
	AIGraphics();
	AIGraphics(thor::ResourceHolder<sf::Texture, std::string>& holder, const std::string& ID);
	~AIGraphics();

	sf::Sprite& GetSprite();
	void Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& interpolation);
};


#pragma once
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>
#include <Thor/Animations.hpp>

#include "GraphicsComponent.hpp"

class PlayerGraphics : public GraphicsComponent
{
private:
	sf::Sprite _sprite;

public:
	PlayerGraphics();
	PlayerGraphics(thor::ResourceHolder<sf::Texture, std::string>& holder, const std::string& ID);
	~PlayerGraphics();

	sf::Sprite& GetSprite();
	void Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& interpolation);
};
#pragma once
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>

class PlayerGraphics
{
private:
	sf::Sprite _sprite;

public:
	PlayerGraphics();
	PlayerGraphics(sf::Texture& texture);
	~PlayerGraphics();

	sf::Sprite& GetSprite();
	void Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& interpolation);
};
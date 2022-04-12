#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>

class PlayerGraphics
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
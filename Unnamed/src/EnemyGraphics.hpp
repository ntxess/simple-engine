#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>

class EnemyGraphics
{
private:
	sf::Sprite _sprite;

public:
	EnemyGraphics();
	EnemyGraphics(thor::ResourceHolder<sf::Texture, std::string>& holder, const std::string& ID);
	~EnemyGraphics();

	sf::Sprite& GetSprite();
	void Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& interpolation);
};


#pragma once
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>

class EnemyGraphics
{
private:
	sf::Sprite _sprite;

public:
	EnemyGraphics();
	EnemyGraphics(sf::Texture& texture);
	~EnemyGraphics();

	sf::Sprite& GetSprite();
	void Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& interpolation);
};


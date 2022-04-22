#pragma once
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>

class UEnemyGraphics
{
private:
	sf::Sprite _sprite;

public:
	UEnemyGraphics();
	UEnemyGraphics(sf::Texture& texture);
	~UEnemyGraphics();

	sf::Sprite& GetSprite();
	void Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& interpolation);
};


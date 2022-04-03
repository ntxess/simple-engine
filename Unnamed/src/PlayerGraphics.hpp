#pragma once
#include <SFML/Graphics.hpp>
#include <Thor/Animations.hpp>

#include "Player.hpp"

class Player;

typedef std::unique_ptr<sf::RenderWindow> RenderWindowRef;

class PlayerGraphics
{
	friend class Player;
	friend class PlayerPhysics;

private:
	sf::Sprite _sprite;
	thor::Animator<sf::Sprite, std::string> _animator;

public:
	PlayerGraphics();
	~PlayerGraphics();

	sf::Sprite& GetSprite();
	void Animator(const Player& player);
	void Render(const RenderWindowRef& rw, const float& deltaTime, const float& interpolation);
};


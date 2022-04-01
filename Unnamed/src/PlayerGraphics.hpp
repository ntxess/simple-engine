#pragma once
#include <SFML/Graphics.hpp>
#include <Thor/Animations.hpp>

#include "PlayerNew.hpp"

class PlayerNew;

typedef std::unique_ptr<sf::RenderWindow> RenderWindowRef;

class PlayerGraphics
{
	friend class PlayerPhysics;

private:
	sf::Sprite _sprite;
	thor::Animator<sf::Sprite, std::string> _animator;

public:
	PlayerGraphics();
	~PlayerGraphics();

	void Animator(PlayerNew& player, float deltaTime, float interpolation);
	void Render(RenderWindowRef& rw, float interpolation);
};


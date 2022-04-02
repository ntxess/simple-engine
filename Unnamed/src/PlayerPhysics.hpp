#pragma once

#include "Player.hpp"

class Player;

class PlayerPhysics
{
private:
	const sf::Vector2u _bounds;

public:
	PlayerPhysics();
	~PlayerPhysics();

	bool OutOfBounds(const Player& player);
	void Update(const Player& player, float deltaTime);
};

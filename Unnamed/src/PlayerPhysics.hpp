#pragma once

#include "Player.hpp"

class Player;

class PlayerPhysics
{
	friend class Player;

private:
	sf::Vector2f _previousPos;

public:
	PlayerPhysics();
	~PlayerPhysics();

	void Update(const Player& player, float deltaTime);
};

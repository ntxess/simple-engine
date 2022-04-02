#pragma once

#include "Player.hpp"

class Player;

class PlayerPhysics
{
public:
	PlayerPhysics();
	~PlayerPhysics();

	void Update(Player& player, float deltaTime);
};

#pragma once
#include <iostream>

#include "Player.hpp"

class Player;

class PlayerPhysics
{
	friend class Player;

public:
	PlayerPhysics();
	~PlayerPhysics();

	void Update(const Player& player, const float& deltaTime);
};

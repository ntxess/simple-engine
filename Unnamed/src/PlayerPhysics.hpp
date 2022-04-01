#pragma once

#include "PlayerNew.hpp"

class PlayerNew;

class PlayerPhysics
{
public:
	PlayerPhysics();
	~PlayerPhysics();

	void Update(PlayerNew& player, float deltaTime);
};


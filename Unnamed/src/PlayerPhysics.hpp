#pragma once

#include "PlayerObject.hpp"

class PlayerPhysics
{
private:
	sf::Vector2f _velocity;

public:
	PlayerPhysics();
	~PlayerPhysics();

	sf::Vector2f GetVelocity() const;
	void Update(const PlayerObject& player, const float& deltaTime);
};

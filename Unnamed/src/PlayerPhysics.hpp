#pragma once

#include "Player.hpp"

class Player;

class PlayerPhysics
{
	friend class Player;

private:
	sf::Vector2f _velocity;

public:
	PlayerPhysics();
	~PlayerPhysics();

	sf::Vector2f GetVelocity() const;
	void Update(const Player& player, const float& deltaTime);
};

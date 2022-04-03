#pragma once

#include "Command.hpp"
#include "Player.hpp"

class CommandDodge : public Command
{
private:
	sf::Clock _timer;
	const float _cooldownTime;

public:
	CommandDodge();
	~CommandDodge();

	void Execute(const Player& player);
};
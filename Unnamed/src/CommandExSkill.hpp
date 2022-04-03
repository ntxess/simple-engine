#pragma once

#include "Command.hpp"
#include "Player.hpp"

class CommandExSkill : public Command
{
private:
	sf::Clock _timer;
	const float _cooldownTime;

public:
	CommandExSkill();
	~CommandExSkill();

	void Execute(const Player& player);
};
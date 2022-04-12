#pragma once

#include "Command.hpp"
#include "PlayerObject.hpp"

class CommandExSkill : public Command
{
private:
	sf::Clock _timer;
	const float _cooldownTime;

public:
	CommandExSkill();
	~CommandExSkill();

	void Execute(const PlayerObject& player);
};
#pragma once

#include "Command.hpp"
#include "Player.hpp"

class CommandExSkill : public Command
{
public:
	CommandExSkill();
	~CommandExSkill();

	void Execute(const Player& player);
};
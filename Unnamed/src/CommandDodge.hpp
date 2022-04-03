#pragma once

#include "Command.hpp"
#include "Player.hpp"

class CommandDodge : public Command
{
public:
	CommandDodge();
	~CommandDodge();

	void Execute(const Player& player);
};




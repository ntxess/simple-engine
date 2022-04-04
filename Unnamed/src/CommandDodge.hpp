#pragma once

#include "Command.hpp"
#include "GameObject.hpp"

class CommandDodge : public Command
{
private:
	sf::Clock _timer;
	const float _cooldownTime;
	const float _dodgeOffset;

public:
	CommandDodge();
	~CommandDodge();

	void Execute(const GameObject& player);
};
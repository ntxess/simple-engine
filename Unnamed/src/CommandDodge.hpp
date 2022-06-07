#pragma once

#include "Command.hpp"
#include "Component.hpp"

class CommandDodge : public Command
{
public:
	sf::Clock _timer;
	float _cooldownTime;
	float _dodgeOffset;

public:
	CommandDodge();
	~CommandDodge();

	float GetTime() const;
	float GetMaxTime() const;
	void Execute(entt::entity entity, entt::registry* registry);
};
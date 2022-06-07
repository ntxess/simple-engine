#pragma once

#include "Command.hpp"
#include "Component.hpp"

class CommandExSkill : public Command
{
public:
	sf::Clock _timer;
	float _cooldownTime;

public:
	CommandExSkill();
	~CommandExSkill();

	float GetTime() const;
	float GetMaxTime() const;
	void Execute(entt::entity entity, entt::registry* registry);
};
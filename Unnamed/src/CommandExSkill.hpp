#pragma once

#include "Command.hpp"
#include "PlayerObject.hpp"
#include "Component.hpp"

class CommandExSkill : public Command
{
private:
	sf::Clock _timer;
	const float _cooldownTime;

public:
	CommandExSkill();
	~CommandExSkill();

	void Execute(const PlayerObject& player);
	void Execute(entt::entity entity, entt::registry* registry);
};
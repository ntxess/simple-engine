#pragma once

#include "Command.hpp"
#include "Component.hpp"

class CommandBasic : public Command
{
public:
	sf::Clock _timer;
	float _cooldownTime;

public:
	CommandBasic();
	~CommandBasic();

	float GetTime() const;
	float GetMaxTime() const;
	void Execute(entt::registry& registry, entt::entity entity, std::shared_ptr<GameData>& data);
};


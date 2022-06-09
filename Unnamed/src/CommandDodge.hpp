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
	void Execute(entt::registry& registry, entt::entity entity, std::shared_ptr<GameData>& data);
};
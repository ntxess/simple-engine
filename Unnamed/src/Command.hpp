#pragma once
#include <iostream>
#include <entt/entt.hpp>

class PlayerObject;

class Command
{
public:
	virtual float GetTime() const = 0;
	virtual float GetMaxTime() const = 0;
	virtual void Execute(const PlayerObject& player) = 0;
	virtual void Execute(entt::entity entity, entt::registry* registry) = 0;
};
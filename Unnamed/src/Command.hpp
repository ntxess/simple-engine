#pragma once

#include "entt/entt.hpp"
#include "GameData.hpp"

class Command
{
public:
	virtual ~Command() {};
	virtual float GetTime() const = 0;
	virtual float GetMaxTime() const = 0;
	virtual void Execute(entt::registry& registry, entt::entity entity, std::shared_ptr<GameData>& data) = 0;
};
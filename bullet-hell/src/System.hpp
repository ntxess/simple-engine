#pragma once
#include "entt/entt.hpp"

class System
{
public:
	virtual ~System() = default;
	virtual void Update(const float& dt, entt::registry& reg, entt::entity ent = entt::null) = 0;
};


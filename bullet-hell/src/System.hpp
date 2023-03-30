#pragma once
#include "entt/entt.hpp"

class System
{
public:
	virtual ~System() = default;
	virtual void Update(entt::registry& reg, const float& dt = 0.f, entt::entity ent = entt::null) = 0;
};


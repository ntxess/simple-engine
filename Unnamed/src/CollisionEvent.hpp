#pragma once
#include <entt/entt.hpp>

#include "Event.hpp"

class CollisionEvent : public Event
{
private:
	entt::entity _inflictor;
	entt::entity _inflicted;

public:
	CollisionEvent(entt::entity inflictor, entt::entity inflicted);
	~CollisionEvent();

	entt::entity GetInflictor();
	entt::entity GetInflicted();
};


#pragma once
#include <typeindex>

#include "entt/entt.hpp"

class Event
{
public:
	virtual ~Event() {};
};

struct DestructionEvent : public Event
{
	entt::entity entityToBeDestroyed;

	DestructionEvent() = default;
	DestructionEvent(const entt::entity& entity)
		: entityToBeDestroyed(entity) {}
	DestructionEvent(const DestructionEvent&) = default;
};

struct CollisionEvent : public Event
{
	entt::entity inflictor;
	entt::entity inflicted;

	CollisionEvent() = default;
	CollisionEvent(const entt::entity& inflictor, const entt::entity& inflicted)
		: inflictor(inflictor), inflicted(inflicted) {}
	CollisionEvent(const CollisionEvent&) = default;
};



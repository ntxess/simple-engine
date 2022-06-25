#include "CollisionEvent.hpp"

CollisionEvent::CollisionEvent(entt::entity inflictor, entt::entity inflicted)
	: Event(Event::Type::Collision), _inflictor(inflictor), _inflicted(inflicted) 
{}

CollisionEvent::~CollisionEvent()
{
}

entt::entity CollisionEvent::GetInflictor()
{
	return _inflictor;
}

entt::entity CollisionEvent::GetInflicted()
{
	return _inflicted;
}

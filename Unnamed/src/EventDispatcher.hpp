#pragma once

#include "Event.hpp"
#include "EventHandler.hpp"

#include <memory>
#include "CollisionEvent.hpp"

class EventDispatcher
{
private:
	Event _event;

public:
	EventDispatcher(Event event);
	~EventDispatcher();

	void Dispatch(Event::Type type, EventHandler handler);

	template<typename T, typename EventType>
	void Dispatch(Event::Type type, T const&t, void(T::* callbackEvent)(Event event));
};

template<typename T, typename EventType>
void EventDispatcher::Dispatch(Event::Type type, T const& t, void(T::*callbackEvent)(Event event))
{
	if (_event.handled)
		return;

	if (_event.GetType() == type)
		t.*callbackEvent(static_cast<EventType>(Event));
}

//bool onCollision(CollisionEvent e)
//{
//	_registry.destroy(e.GetInflictor());
//	_registry.destroy(e.GetInflicted());
//	return false;
//}
//
//entt::entity inflictor, inflicted;
//std::unique_ptr<CollisionEvent> collisionEvent = std::make_unique<CollisionEvent>(inflictor, inflicted);
//
//
//std::unique_ptr<EventDispatcher> dispatcher = std::make_unique<EventDispatcher>(collisionEvent.get());
//dispatcher->Dispatch(Event::Type::Collision, std::make_unqiue<EventHandler>());



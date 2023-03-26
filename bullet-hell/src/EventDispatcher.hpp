#pragma once
#include "Event.hpp"

class EventDispatcher
{
public:
	EventDispatcher() {}
	~EventDispatcher() {}

	template<typename T, typename EventType>
	void Dispatch(Event* evnt, T* instance, void (T::* callbackEvent)(EventType*));
};

template<typename T, typename EventType>
void EventDispatcher::Dispatch(Event* evnt, T* instance, void (T::*callbackEvent)(EventType *))
{	
	(instance->*callbackEvent)(static_cast<EventType*>(evnt));
}

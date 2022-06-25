#include "EventDispatcher.hpp"

EventDispatcher::EventDispatcher(Event event)
	: _event(event)
{}

EventDispatcher::~EventDispatcher()
{}

void EventDispatcher::Dispatch(Event::Type type, EventHandler handler)
{
	if (_event.handled)
		return;

	if (_event.GetType() == type)
		_event.handled = handler.OnEvent(_event);
}
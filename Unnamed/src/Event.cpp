#include "Event.hpp"

Event::Event(Type type)
	: _type(type)
{}

Event::~Event()
{}

Event::Type Event::GetType()
{
	return _type;
}

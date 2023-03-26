#pragma once
#include "Event.hpp"

class EventHandler
{
public:
	virtual ~EventHandler() {}
	virtual void OnEvent(Event* evnt) = 0;
};

class DestructionHandler : public EventHandler
{
public:
	DestructionHandler() {}
	~DestructionHandler() {}

	void OnEvent(Event* evnt)
	{
		//evnt->entityToBeDestroyed
		//std::cout << "Destruction Event Triggered\n";
	}
};

class CollisionHandler : public EventHandler
{
public:
	CollisionHandler() {}
	~CollisionHandler() {}

	void OnEvent(Event* evnt)
	{
		std::cout << "Collision Event Triggered\n";
	}
};
#pragma once

#include "WayPoint.hpp"

struct MStraight
{
public:
	std::unique_ptr<WayPoint> head;

	MStraight()
	{
		std::unique_ptr<WayPoint> pointA = std::make_unique<WayPoint>(sf::Vector2f(0.0f, 0.0f));
		std::unique_ptr<WayPoint> pointB = std::make_unique<WayPoint>(sf::Vector2f(0.0f, -1000.0f));

		pointA->AddNext(std::move(pointB));

		head = std::move(pointA);

		// Setting distance between WayPoints
		WayPoint* headPtr = head.get();
		WayPoint* next;
		while (headPtr->_nextWP.get() != NULL)
		{
			next = headPtr->_nextWP.get();
			headPtr->_nextWP.get()->_distanceTotal = headPtr->_distanceTotal + headPtr->_distanceToNext;
			headPtr = next;
		}
	}

	~MStraight()
	{}
};
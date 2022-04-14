#pragma once

#include "WayPoint.hpp"

struct MCircle
{
public:
	WayPoint* _startingWP;

	MCircle()
	{
		std::unique_ptr<WayPoint> pointA = std::make_unique<WayPoint>(sf::Vector2f(120.0f, 80.0f));
		std::unique_ptr<WayPoint> pointB = std::make_unique<WayPoint>(sf::Vector2f(210.0f, 30.0f));
		std::unique_ptr<WayPoint> pointC = std::make_unique<WayPoint>(sf::Vector2f(260.0f, 120.0f));
		std::unique_ptr<WayPoint> pointD = std::make_unique<WayPoint>(sf::Vector2f(180.0f, 190.0f));
		std::unique_ptr<WayPoint> pointE = std::make_unique<WayPoint>(sf::Vector2f(80.0f, 140.0f));

		pointA->AddNext(pointB.get());
		pointB->AddNext(pointC.get());
		pointC->AddNext(pointD.get());
		pointD->AddNext(pointE.get());

		_startingWP = pointA.get();
	}

	~MCircle(){}
};
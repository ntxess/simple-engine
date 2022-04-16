#pragma once

#include "WayPoint.hpp"

struct MCircle
{
public:
	std::unique_ptr<WayPoint> head;

	MCircle()
	{
		std::unique_ptr<WayPoint> pointA = std::make_unique<WayPoint>(sf::Vector2f(120.0f, 80.0f));
		std::unique_ptr<WayPoint> pointB = std::make_unique<WayPoint>(sf::Vector2f(210.0f, 30.0f));
		std::unique_ptr<WayPoint> pointC = std::make_unique<WayPoint>(sf::Vector2f(260.0f, 120.0f));
		std::unique_ptr<WayPoint> pointD = std::make_unique<WayPoint>(sf::Vector2f(180.0f, 190.0f));
		std::unique_ptr<WayPoint> pointE = std::make_unique<WayPoint>(sf::Vector2f(80.0f, 140.0f));

		//std::unique_ptr<WayPoint> pointA = std::make_unique<WayPoint>(sf::Vector2f(80.0f, 140.0f));
		//std::unique_ptr<WayPoint> pointB = std::make_unique<WayPoint>(sf::Vector2f(180.0f, 190.0f));
		//std::unique_ptr<WayPoint> pointC = std::make_unique<WayPoint>(sf::Vector2f(260.0f, 120.0f));
		//std::unique_ptr<WayPoint> pointD = std::make_unique<WayPoint>(sf::Vector2f(210.0f, 30.0f));
		//std::unique_ptr<WayPoint> pointE = std::make_unique<WayPoint>(sf::Vector2f(120.0f, 80.0f));

		pointD->AddNext(std::move(pointE));
		pointC->AddNext(std::move(pointD));
		pointB->AddNext(std::move(pointC));
		pointA->AddNext(std::move(pointB));

		head = std::move(pointA);

		WayPoint* headPtr = head.get();
		WayPoint* next;
		while (headPtr != NULL)
		{
			std::cout << "=========================MCIRCLE=========================" << std::endl;
			next = headPtr->_nextWP.get();
			std::cout << "ADDRESS   : " << &*(headPtr) << " " << &*(headPtr->_nextWP) << std::endl;
			std::cout << "LOCATION  : " << headPtr->_location.x << " " << headPtr->_location.y << std::endl;
			std::cout << "DISTANCE N: " << headPtr->_distanceToNext << std::endl;
			std::cout << "DISTANCE T: " << headPtr->_distanceTotal << std::endl;
			headPtr = next;
		}
	}

	~MCircle()
	{}
};